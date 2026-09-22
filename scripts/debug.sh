#!/usr/bin/env bash
# 针对某道题目的某一组测试用例启动交互式调试（C++ 用 gdb/lldb，Python 用 pdb），
# 并把该用例的输入作为程序的 stdin。
#
# 用法:
#   scripts/debug.sh <题目目录> <用例编号>
#
# 示例:
#   scripts/debug.sh problems/examples/a-plus-b 1
#
# 支持环境:
#   - C++ 题目（solution.cpp）：WSL/Linux 用 gdb，macOS 用 lldb
#   - Python 题目（solution.py）：跨平台统一用 python3 -m pdb，不区分操作系统

set -uo pipefail

# 仓库根目录（本脚本位于 <仓库根>/scripts/ 下），用于定位 common/ 共享头文件目录，
# 不依赖调用脚本时的当前工作目录。
script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(dirname "$script_dir")
common_dir="$repo_root/common"

# detect_language / language_conflict_message / language_missing_message：
# 与 scripts/run_tests.sh 共用同一份语言判定逻辑和报错文案。
source "$script_dir/lib/problem_language.sh"

usage() {
    echo "用法: $0 <题目目录> <用例编号>" >&2
    echo "示例: $0 problems/examples/a-plus-b 1" >&2
    exit 2
}

if [[ $# -ne 2 ]]; then
    usage
fi

problem_dir="$1"
case_name="$2"
input_file="$problem_dir/tests/$case_name.in"

language=
detect_language "$problem_dir" language

case "$language" in
    both)
        language_conflict_message "$problem_dir" >&2
        exit 2
        ;;
    none)
        language_missing_message "$problem_dir" >&2
        exit 2
        ;;
esac

if [[ ! -f "$input_file" ]]; then
    echo "错误: 未找到测试用例输入 $input_file" >&2
    exit 2
fi

if [[ "$language" == python ]]; then
    PYTHON_BIN="${PYTHON_BIN:-python3}"
    solution="$problem_dir/solution.py"

    if ! command -v "$PYTHON_BIN" >/dev/null 2>&1; then
        echo "错误: 未找到 Python 解释器 $PYTHON_BIN，请先运行 scripts/setup.sh 完成环境初始化。" >&2
        exit 2
    fi

    if ! ( exec 3<>/dev/tty ) 2>/dev/null; then
        echo "错误: 无法访问 /dev/tty，pdb 交互式调试需要一个真实终端（不能在无终端的自动化环境中运行）。" >&2
        exit 2
    fi

    echo "正在启动 pdb 调试 $solution，输入来自: $input_file"
    # pdb 自身的命令行（断点、单步等）需要读写真实终端 /dev/tty；被调试脚本的
    # input()/sys.stdin 则重定向到该用例的输入文件。两者共用同一个进程 stdin 时
    # 会互相抢占（pdb 会把测试输入当成调试命令解析），所以这里显式拆开两路 I/O，
    # 而不是简单地用 `python3 -m pdb solution.py < input_file`。
    exec "$PYTHON_BIN" - "$solution" "$input_file" <<'PYEOF'
import pdb
import sys

solution_path = sys.argv[1]
input_path = sys.argv[2]

tty_in = open("/dev/tty", "r")
tty_out = open("/dev/tty", "w", buffering=1)
sys.stdin = open(input_path, "r")

debugger = pdb.Pdb(stdin=tty_in, stdout=tty_out)
with open(solution_path) as f:
    source = f.read()
debugger.run(compile(source, solution_path, "exec"), {"__name__": "__main__"})
PYEOF
fi

solution="$problem_dir/solution.cpp"
CXX="${CXX:-g++}"

if ! command -v "$CXX" >/dev/null 2>&1; then
    echo "错误: 未找到编译器 $CXX，请先运行 scripts/setup.sh 完成环境初始化。" >&2
    exit 2
fi

work_dir=$(mktemp -d)
trap 'rm -rf "$work_dir"' EXIT

binary="$work_dir/solution_debug"

echo "正在以调试符号编译 $solution ..."
if ! "$CXX" -g -O0 -std=c++17 -Wall -I "$common_dir" -o "$binary" "$solution" 2> "$work_dir/compile.log"; then
    echo "编译失败:" >&2
    cat "$work_dir/compile.log" >&2
    exit 2
fi

os_name=$(uname -s)

case "$os_name" in
    Darwin)
        if ! command -v lldb >/dev/null 2>&1; then
            echo "错误: 未找到 lldb，请先安装 Xcode Command Line Tools（xcode-select --install）。" >&2
            exit 2
        fi
        echo "正在启动 lldb，输入来自: $input_file"
        echo "提示: 在 lldb 中运行 'process launch -i $input_file' 来重定向 stdin 并开始调试。"
        exec lldb "$binary"
        ;;
    Linux)
        if ! command -v gdb >/dev/null 2>&1; then
            echo "错误: 未找到 gdb，请先运行 scripts/setup.sh 或手动安装 gdb。" >&2
            exit 2
        fi
        echo "正在启动 gdb，输入来自: $input_file"
        echo "提示: 在 gdb 提示符下先设置断点（如 'break main'），再输入以下命令开始运行并重定向输入:"
        echo "  run < $input_file"
        exec gdb -q "$binary"
        ;;
    *)
        echo "错误: 暂不支持的操作系统: $os_name" >&2
        exit 1
        ;;
esac
