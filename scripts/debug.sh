#!/usr/bin/env bash
# 针对某道题目的某一组测试用例启动交互式调试（gdb 或 lldb），并把该用例的输入作为
# 程序的 stdin。
#
# 用法:
#   scripts/debug.sh <题目目录> <用例编号>
#
# 示例:
#   scripts/debug.sh problems/examples/a-plus-b 1
#
# 支持环境:
#   - WSL/Linux: 使用 gdb
#   - macOS: 使用 lldb

set -uo pipefail

# 仓库根目录（本脚本位于 <仓库根>/scripts/ 下），用于定位 common/ 共享头文件目录，
# 不依赖调用脚本时的当前工作目录。
script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(dirname "$script_dir")
common_dir="$repo_root/common"

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
solution="$problem_dir/solution.cpp"
input_file="$problem_dir/tests/$case_name.in"

if [[ ! -f "$solution" ]]; then
    echo "错误: 未找到解答文件 $solution" >&2
    exit 2
fi

if [[ ! -f "$input_file" ]]; then
    echo "错误: 未找到测试用例输入 $input_file" >&2
    exit 2
fi

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
