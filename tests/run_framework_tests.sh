#!/usr/bin/env bash
# 针对 scripts/run_tests.sh 本身的自测：验证多用例聚合、PASS/FAIL 判定与失败定位。
#
# 用法:
#   tests/run_framework_tests.sh

set -uo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(cd "$script_dir/.." && pwd)
run_tests="$repo_root/scripts/run_tests.sh"
fixtures="$script_dir/framework/fixtures"

overall_fail=0

echo "== 自测 1: passing-problem 应全部 PASS，命令应返回 0 =="
output=$("$run_tests" "$fixtures/passing-problem" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 0 ]]; then
    echo "结果: FAILED（期望退出码 0，实际 $exit_code）"
    overall_fail=1
elif ! echo "$output" | grep -q "结果: 1/1 通过"; then
    echo "结果: FAILED（未检测到期望的 1/1 通过汇总）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 2: failing-problem 应检测到 1 个 FAIL，命令应返回非 0 =="
output=$("$run_tests" "$fixtures/failing-problem" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -eq 0 ]]; then
    echo "结果: FAILED（期望非零退出码，实际 0）"
    overall_fail=1
elif ! echo "$output" | grep -q "^\[1\] PASS"; then
    echo "结果: FAILED（用例 1 应为 PASS，用于验证部分通过场景）"
    overall_fail=1
elif ! echo "$output" | grep -q "^\[2\] FAIL"; then
    echo "结果: FAILED（用例 2 应为 FAIL）"
    overall_fail=1
elif ! echo "$output" | grep -q "结果: 1/2 通过"; then
    echo "结果: FAILED（未检测到期望的 1/2 通过汇总）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
if [[ $overall_fail -eq 0 ]]; then
    echo "框架自测全部通过"
    exit 0
else
    echo "框架自测存在失败"
    exit 1
fi
