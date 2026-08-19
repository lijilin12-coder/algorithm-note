#!/usr/bin/env bash
# 编译题目解答并运行全部测试用例，逐用例报告 PASS/FAIL。
#
# 用法:
#   scripts/run_tests.sh <题目目录>
#
# <题目目录> 直接包含 solution.cpp 时，按单题目模式运行。
# <题目目录> 不直接包含 solution.cpp 时，按批量模式运行：递归扫描该目录下所有
# 同时包含 solution.cpp 与 tests/ 的子目录（不限层级），按路径排序依次运行；
# 某个题目失败（编译失败或有用例 FAIL）时跳过该题目，继续运行后续题目，最后
# 汇总输出所有失败的题目；只要有题目失败，脚本整体以非 0 状态退出。
#
# 示例:
#   scripts/run_tests.sh problems/examples/a-plus-b   # 单题目
#   scripts/run_tests.sh problems/examples            # 批量：该分类下所有题目
#   scripts/run_tests.sh problems                      # 批量：全部题目
#
# 题目目录约定见 problems/README.md：
#   <题目目录>/solution.cpp
#   <题目目录>/tests/<编号>.in
#   <题目目录>/tests/<编号>.ans

set -uo pipefail

# 仓库根目录（本脚本位于 <仓库根>/scripts/ 下），用于定位 common/ 共享头文件目录，
# 不依赖调用脚本时的当前工作目录。
script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(dirname "$script_dir")
common_dir="$repo_root/common"

usage() {
    echo "用法: $0 <题目目录>" >&2
    echo "示例: $0 problems/examples/a-plus-b" >&2
    echo "      $0 problems/examples  (批量运行该目录下所有题目)" >&2
    exit 2
}

if [[ $# -ne 1 ]]; then
    usage
fi

target_dir="$1"

if [[ ! -d "$target_dir" ]]; then
    echo "错误: 目录不存在 $target_dir" >&2
    exit 2
fi

CXX="${CXX:-g++}"

if ! command -v "$CXX" >/dev/null 2>&1; then
    echo "错误: 未找到编译器 $CXX，请先运行 scripts/setup.sh 完成环境初始化。" >&2
    exit 2
fi

print_block() {
    local title="$1"
    local file_path="$2"

    echo "    $title:"
    if [[ -s "$file_path" ]]; then
        sed 's/^/      /' "$file_path"
    else
        echo "      <空>"
    fi
}

# 编译并运行单个题目目录的全部测试用例，输出逐用例 PASS/FAIL。
# 成功（全部用例通过）返回 0，用例 FAIL 返回 1，环境/参数错误返回 2。
run_one_problem() {
    local problem_dir="$1"
    local solution="$problem_dir/solution.cpp"
    local tests_dir="$problem_dir/tests"

    if [[ ! -f "$solution" ]]; then
        echo "错误: 未找到解答文件 $solution" >&2
        return 2
    fi

    if [[ ! -d "$tests_dir" ]]; then
        echo "错误: 未找到测试用例目录 $tests_dir" >&2
        return 2
    fi

    local work_dir
    work_dir=$(mktemp -d)
    # shellcheck disable=SC2064
    trap "rm -rf '$work_dir'" RETURN

    local binary="$work_dir/solution"

    echo "正在编译 $solution ..."
    if ! "$CXX" -O2 -std=c++17 -Wall -I "$common_dir" -o "$binary" "$solution" 2> "$work_dir/compile.log"; then
        echo "编译失败:" >&2
        cat "$work_dir/compile.log" >&2
        return 2
    fi

    local pass_count=0
    local fail_count=0
    local ran_any=0

    for input_file in "$tests_dir"/*.in; do
        [[ -e "$input_file" ]] || continue
        ran_any=1
        local case_name
        case_name=$(basename "$input_file" .in)
        local expected_file="$tests_dir/$case_name.ans"

        if [[ ! -f "$expected_file" ]]; then
            echo "[$case_name] SKIP (缺少期望输出 $expected_file)"
            continue
        fi

        local actual_file="$work_dir/$case_name.actual"
        local stderr_file="$work_dir/$case_name.stderr"

        if ! "$binary" < "$input_file" > "$actual_file" 2> "$stderr_file"; then
            echo "[$case_name] FAIL (运行时错误，退出码非 0)"
            if [[ -s "$stderr_file" ]]; then
                sed 's/^/    /' "$stderr_file"
            fi
            fail_count=$((fail_count + 1))
            continue
        fi

        if diff -q -b -B "$actual_file" "$expected_file" > /dev/null 2>&1; then
            echo "[$case_name] PASS"
            pass_count=$((pass_count + 1))
        else
            echo "[$case_name] FAIL"
            print_block "期望输出" "$expected_file"
            print_block "实际输出" "$actual_file"
            fail_count=$((fail_count + 1))
        fi
    done

    if [[ $ran_any -eq 0 ]]; then
        echo "错误: $tests_dir 下没有找到任何 *.in 测试用例" >&2
        return 2
    fi

    local total=$((pass_count + fail_count))
    echo ""
    echo "结果: $pass_count/$total 通过"

    if [[ $fail_count -gt 0 ]]; then
        return 1
    fi
    return 0
}

if [[ -f "$target_dir/solution.cpp" ]]; then
    run_one_problem "$target_dir"
    exit $?
fi

# 批量模式：递归发现所有包含 solution.cpp 的子目录，按路径排序依次运行。
# 用 while read 而非 mapfile 读取，兼容 macOS 自带的 Bash 3.2（无 mapfile 内建命令）。
problem_solutions=()
while IFS= read -r solution_path; do
    problem_solutions+=("$solution_path")
done < <(find "$target_dir" -type f -name solution.cpp | sort)

if [[ ${#problem_solutions[@]} -eq 0 ]]; then
    echo "错误: $target_dir 下没有找到任何题目（solution.cpp）" >&2
    exit 2
fi

problem_count=${#problem_solutions[@]}
ran_count=0
failed_problems=()

for solution_path in "${problem_solutions[@]}"; do
    problem_dir=$(dirname "$solution_path")
    ran_count=$((ran_count + 1))
    echo "=== [$ran_count/$problem_count] $problem_dir ==="
    run_one_problem "$problem_dir"
    status=$?
    if [[ $status -ne 0 ]]; then
        echo "题目 $problem_dir 失败，跳过并继续运行后续题目。" >&2
        failed_problems+=("$problem_dir")
    fi
    echo ""
done

if [[ ${#failed_problems[@]} -gt 0 ]]; then
    echo "批量测试结果: 共运行 $problem_count 个题目，${#failed_problems[@]} 个失败："
    for failed_dir in "${failed_problems[@]}"; do
        echo "  - $failed_dir"
    done
    exit 1
fi

echo "批量测试结果: 共运行 $problem_count 个题目，全部通过"
exit 0
