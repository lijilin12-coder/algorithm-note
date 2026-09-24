#!/usr/bin/env bash
# 针对 scripts/run_tests.sh 本身的自测：验证多用例聚合、PASS/FAIL 判定与失败定位；
# 并在 Linux 上模拟 Windows（Git Bash）环境，验证 run_tests/setup/debugpy_listen 的兼容逻辑。
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
echo "== 自测 3: python-passing-problem 应全部 PASS，命令应返回 0（Python 单题目模式） =="
output=$("$run_tests" "$fixtures/python-passing-problem" 2>&1)
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
echo "== 自测 4: python-failing-problem 应检测到 1 个 FAIL，命令应返回非 0（Python） =="
output=$("$run_tests" "$fixtures/python-failing-problem" 2>&1)
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
echo "== 自测 5: both-language-problem（solution.cpp 与 solution.py 同时存在）应明确报错 =="
output=$("$run_tests" "$fixtures/both-language-problem" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -eq 0 ]]; then
    echo "结果: FAILED（期望非零退出码，实际 0）"
    overall_fail=1
elif ! echo "$output" | grep -q "二选一"; then
    echo "结果: FAILED（未检测到二选一的报错提示）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 6: 混合批量模式（C++ + Python 题目同批次）全部 PASS 应返回 0 =="
batch_dir=$(mktemp -d)
trap 'rm -rf "$batch_dir"' EXIT
cp -R "$fixtures/passing-problem" "$batch_dir/cpp-problem"
cp -R "$fixtures/python-passing-problem" "$batch_dir/python-problem"
output=$("$run_tests" "$batch_dir" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 0 ]]; then
    echo "结果: FAILED（期望退出码 0，实际 $exit_code）"
    overall_fail=1
elif ! echo "$output" | grep -q "共运行 2 个题目，全部通过"; then
    echo "结果: FAILED（未检测到期望的 2 个题目全部通过汇总）"
    overall_fail=1
else
    echo "结果: OK"
fi
rm -rf "$batch_dir"

# ---- Windows（Git Bash）兼容性自测：在 Linux 上用伪造的 uname / PATH 模拟 ----

sim_dir=$(mktemp -d)
trap 'rm -rf "$batch_dir" "$sim_dir"' EXIT

# 隔离 setup.sh 的用户 PATH 写入：在真实 Windows 上跑自测时，不能读到真实的
# MSYS2 安装或调用真实 powershell.exe 改注册表。需要验证该行为的自测单独覆盖。
export MSYS2_ROOT="$sim_dir/no-msys2"
export POWERSHELL_BIN=false

# 伪造 uname -s 输出 Windows Git Bash 的系统名。
win_bin="$sim_dir/win-bin"
mkdir -p "$win_bin"
cat > "$win_bin/uname" <<'SH'
#!/usr/bin/env bash
echo "MINGW64_NT-10.0-19045"
SH
chmod +x "$win_bin/uname"

# 记录 -o 参数的 g++ 包装，用于确认 Windows 下编译产物带 .exe 后缀。
cxx_log="$sim_dir/cxx.log"
cat > "$sim_dir/cxx-wrapper" <<SH
#!/usr/bin/env bash
echo "\$*" >> "$cxx_log"
exec g++ "\$@"
SH
chmod +x "$sim_dir/cxx-wrapper"

echo ""
echo "== 自测 7: Windows 模拟（uname=MINGW64）下批量运行 C++ + Python 题目，C++ 产物为 .exe =="
win_batch="$sim_dir/win-batch"
mkdir -p "$win_batch"
cp -R "$fixtures/passing-problem" "$win_batch/cpp-problem"
cp -R "$fixtures/python-passing-problem" "$win_batch/python-problem"
cp -R "$fixtures/failing-problem" "$win_batch/zz-failing-problem"
output=$(PATH="$win_bin:$PATH" CXX="$sim_dir/cxx-wrapper" "$run_tests" "$win_batch" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 1 ]]; then
    echo "结果: FAILED（期望退出码 1（有一个失败题目），实际 $exit_code）"
    overall_fail=1
elif ! echo "$output" | grep -q "共运行 3 个题目，1 个失败"; then
    echo "结果: FAILED（未检测到期望的 3 个题目 1 个失败汇总）"
    overall_fail=1
elif ! grep -q -- "-o [^ ]*/solution\.exe " "$cxx_log"; then
    echo "结果: FAILED（Windows 模拟下编译产物未使用 .exe 后缀）"
    cat "$cxx_log"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 8: 仅有 python（python3 为无法运行的应用商店占位别名）时 Python 题目仍可运行 =="
py_bin="$sim_dir/py-bin"
mkdir -p "$py_bin"
printf '#!/usr/bin/env bash\necho "Python was not found; run without arguments to install from the Microsoft Store" >&2\nexit 9009\n' > "$py_bin/python3"
chmod +x "$py_bin/python3"
ln -s "$(command -v python3)" "$py_bin/python"
output=$(env -u PYTHON_BIN PATH="$py_bin:$win_bin:$PATH" "$run_tests" "$fixtures/python-passing-problem" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 0 ]]; then
    echo "结果: FAILED（期望退出码 0，实际 $exit_code）"
    overall_fail=1
elif ! echo "$output" | grep -q "使用 python 运行"; then
    echo "结果: FAILED（未回退到 python 解释器）"
    overall_fail=1
else
    output=$(PYTHON_BIN="$py_bin/python" PATH="$py_bin:$PATH" "$run_tests" "$fixtures/python-passing-problem" 2>&1)
    if ! echo "$output" | grep -q "使用 $py_bin/python 运行"; then
        echo "结果: FAILED（显式设置的 PYTHON_BIN 未被优先使用）"
        overall_fail=1
    else
        echo "结果: OK"
    fi
fi

echo ""
echo "== 自测 9: CRLF 行尾的程序输出与 .in/.ans 应与 LF 等价判定为 PASS =="
crlf_dir="$sim_dir/crlf-problem"
mkdir -p "$crlf_dir/tests"
cat > "$crlf_dir/solution.py" <<'PY'
import sys
a, b = map(int, sys.stdin.read().split())
sys.stdout.buffer.write(b"%d\r\n%d\r\n" % (a + b, a * b))
PY
printf '2 3\r\n' > "$crlf_dir/tests/1.in"
printf '5\r\n6\r\n' > "$crlf_dir/tests/1.ans"
printf '4 5\n' > "$crlf_dir/tests/2.in"
printf '9\n20\n' > "$crlf_dir/tests/2.ans"
output=$("$run_tests" "$crlf_dir" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 0 ]] || ! echo "$output" | grep -q "结果: 2/2 通过"; then
    echo "结果: FAILED（CRLF 用例应全部 PASS，实际退出码 $exit_code）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 10: 环境中没有 timeout 命令时不启用超时，题目照常运行 =="
no_timeout_bin="$sim_dir/no-timeout-bin"
mkdir -p "$no_timeout_bin"
for tool_dir in /usr/local/bin /usr/bin /bin; do
    [[ -d "$tool_dir" ]] || continue
    for tool in "$tool_dir"/*; do
        name=$(basename "$tool")
        [[ "$name" == timeout ]] && continue
        [[ -e "$no_timeout_bin/$name" ]] || ln -s "$tool" "$no_timeout_bin/$name"
    done
done
output=$(PATH="$no_timeout_bin" "$run_tests" "$fixtures/passing-problem" 2>&1)
exit_code=$?
echo "$output"
if PATH="$no_timeout_bin" command -v timeout >/dev/null 2>&1; then
    echo "结果: FAILED（模拟环境中仍能找到 timeout，自测前提不成立）"
    overall_fail=1
elif [[ $exit_code -ne 0 ]] || ! echo "$output" | grep -q "结果: 1/1 通过"; then
    echo "结果: FAILED（缺少 timeout 时应照常运行并通过，实际退出码 $exit_code）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 11: Windows 模拟下 setup.sh 已有工具链时只报告版本并成功退出 =="
setup_sh="$repo_root/scripts/setup.sh"
output=$(PATH="$win_bin:$PATH" "$setup_sh" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -ne 0 ]]; then
    echo "结果: FAILED（期望退出码 0，实际 $exit_code）"
    overall_fail=1
elif ! echo "$output" | grep -q "MINGW64" || ! echo "$output" | grep -q "已找到编译器" || ! echo "$output" | grep -q "已找到 Python 解释器"; then
    echo "结果: FAILED（未按 Windows 分支检测并报告已有工具链）"
    overall_fail=1
elif echo "$output" | grep -q "MinGW 目录"; then
    echo "结果: FAILED（工具链已存在且无 MinGW 目录时不应输出用户 PATH 相关信息）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 12: Windows 模拟下缺少编译器且没有 winget 时 setup.sh 报错说明手动安装并以非 0 退出 =="
# 从 PATH 中去掉含 winget 的目录，避免在真实 Windows 上跑自测时真的触发安装。
no_winget_path=$(IFS=:; for d in $PATH; do [[ -e "$d/winget" || -e "$d/winget.exe" ]] || printf '%s:' "$d"; done)
no_winget_path=${no_winget_path%:}
output=$(PATH="$win_bin:$no_winget_path" CXX=no-such-gxx "$setup_sh" 2>&1)
exit_code=$?
echo "$output"
if [[ $exit_code -eq 0 ]]; then
    echo "结果: FAILED（期望非零退出码，实际 0）"
    overall_fail=1
elif ! echo "$output" | grep -q "未检测到 winget" || ! echo "$output" | grep -q "msys2"; then
    echo "结果: FAILED（未给出缺少 winget 时的手动安装说明）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 13: Windows 模拟下 debugpy_listen.sh 用 netstat 识别已占用端口（含本地化状态列） =="
ns_bin="$sim_dir/netstat-bin"
mkdir -p "$ns_bin"
cat > "$ns_bin/netstat" <<'SH'
#!/usr/bin/env bash
printf '\r\nActive Connections\r\n\r\n  Proto  Local Address          Foreign Address        State\r\n'
printf '  TCP    0.0.0.0:135            0.0.0.0:0              LISTENING\r\n'
printf '  TCP    127.0.0.1:15678        127.0.0.1:5000         ESTABLISHED\r\n'
printf '  TCP    127.0.0.1:5678         0.0.0.0:0              ABH\xc3\x96REN\r\n'
printf '  TCP    [::1]:5679             [::]:0                 LISTENING\r\n'
SH
chmod +x "$ns_bin/netstat"
listen_sh="$repo_root/scripts/debugpy_listen.sh"
all_ok=1
for port in 5678 5679; do
    output=$(PATH="$ns_bin:$win_bin:$PATH" "$listen_sh" "$fixtures/python-passing-problem/solution.py" "$fixtures/python-passing-problem/tests/1.in" "$port" 2>&1)
    exit_code=$?
    echo "[端口 $port] $output"
    if [[ $exit_code -ne 2 ]] || ! echo "$output" | grep -q "已被占用"; then
        all_ok=0
    fi
done
if [[ $all_ok -eq 0 ]]; then
    echo "结果: FAILED（应识别出 IPv4/IPv6 上已监听的端口并报“已被占用”）"
    overall_fail=1
else
    echo "结果: OK"
fi

echo ""
echo "== 自测 14: Windows 模拟下 setup.sh 把 MinGW bin 追加到用户 PATH，重复运行不重复添加，失败时给出手动说明 =="
# 用记录调用的 PowerShell 存根代替真实写注册表：用文件模拟用户 PATH。
ps_state="$sim_dir/user-path.txt"
: > "$ps_state"
cat > "$sim_dir/fake-powershell" <<SH
#!/usr/bin/env bash
if grep -qxF "\$SETUP_PATH_DIR" "$ps_state"; then
    echo present
else
    echo "\$SETUP_PATH_DIR" >> "$ps_state"
    echo added
fi
SH
chmod +x "$sim_dir/fake-powershell"
# 编译器存根：让 setup.sh 走“已有工具链”路径，自测只关注用户 PATH 行为。
printf '#!/usr/bin/env bash\necho "g++ (fake) 13.0"\n' > "$sim_dir/fake-gxx"
chmod +x "$sim_dir/fake-gxx"
fake_gxx="$sim_dir/fake-gxx"
fake_msys="$sim_dir/msys64"
all_ok=1
# 目录不存在时不调用 PowerShell。
PATH="$win_bin:$PATH" CXX="$fake_gxx" MSYS2_ROOT="$fake_msys" POWERSHELL_BIN="$sim_dir/fake-powershell" "$setup_sh" >/dev/null 2>&1
[[ -s "$ps_state" ]] && { echo "目录不存在时仍写入了 PATH"; all_ok=0; }
mkdir -p "$fake_msys/ucrt64/bin"
output=$(PATH="$win_bin:$PATH" CXX="$fake_gxx" MSYS2_ROOT="$fake_msys" POWERSHELL_BIN="$sim_dir/fake-powershell" "$setup_sh" 2>&1)
exit_code=$?
echo "[首次] $output"
if [[ $exit_code -ne 0 ]] || ! echo "$output" | grep -q "已把 MinGW 目录加入 Windows 用户 PATH"; then
    all_ok=0
fi
output=$(PATH="$win_bin:$PATH" CXX="$fake_gxx" MSYS2_ROOT="$fake_msys" POWERSHELL_BIN="$sim_dir/fake-powershell" "$setup_sh" 2>&1)
exit_code=$?
echo "[再次] $output"
if [[ $exit_code -ne 0 ]] || echo "$output" | grep -q "MinGW 目录" || [[ $(wc -l < "$ps_state") -ne 1 ]]; then
    all_ok=0
fi
output=$(PATH="$win_bin:$PATH" CXX="$fake_gxx" MSYS2_ROOT="$fake_msys" POWERSHELL_BIN=false "$setup_sh" 2>&1)
exit_code=$?
echo "[失败] $output"
if [[ $exit_code -ne 0 ]] || ! echo "$output" | grep -q "请手动添加"; then
    all_ok=0
fi
if [[ $all_ok -eq 0 ]]; then
    echo "结果: FAILED（用户 PATH 自动添加、幂等或失败回退行为不符合预期）"
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
