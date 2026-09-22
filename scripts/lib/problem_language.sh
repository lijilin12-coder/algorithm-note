# 供 scripts/run_tests.sh 与 scripts/debug.sh 共用：判定某个题目目录使用的解答
# 语言（C++ 的 solution.cpp 或 Python 的 solution.py，二选一），并提供两者同时
# 存在/都不存在时的统一错误文案，避免同一条判断逻辑和文案在多个脚本里各写一份、
# 后续改一处忘了改另一处。
#
# 用 `source` 方式引入，不能独立执行。

# 判定某个题目目录使用的语言，把结果（cpp/python/both/none）写入调用方通过 $2
# 指定的变量名。
detect_language() {
    local problem_dir="$1"
    local __result_var="$2"
    local has_cpp=0
    local has_py=0

    [[ -f "$problem_dir/solution.cpp" ]] && has_cpp=1
    [[ -f "$problem_dir/solution.py" ]] && has_py=1

    if [[ $has_cpp -eq 1 && $has_py -eq 1 ]]; then
        printf -v "$__result_var" 'both'
    elif [[ $has_cpp -eq 1 ]]; then
        printf -v "$__result_var" 'cpp'
    elif [[ $has_py -eq 1 ]]; then
        printf -v "$__result_var" 'python'
    else
        printf -v "$__result_var" 'none'
    fi
}

# 题目目录下 solution.cpp 与 solution.py 同时存在时的统一报错文案。
language_conflict_message() {
    local problem_dir="$1"
    echo "错误: $problem_dir 下 solution.cpp 与 solution.py 同时存在，同一题目只能保留一种语言的解答（solution.cpp 或 solution.py 二选一）。"
}

# 题目目录下两种解答文件都不存在时的统一报错文案。
language_missing_message() {
    local problem_dir="$1"
    echo "错误: 未找到解答文件 $problem_dir/solution.cpp 或 $problem_dir/solution.py"
}
