#!/usr/bin/env bash
# 供 .vscode/tasks.json 中的“启动 Python 调试目标（debugpy 监听）”任务调用：以
# debugpy --wait-for-client 启动指定的 Python 题目脚本，把给定用例输入重定向为
# 其 stdin，并在监听端口真正可连接后打印固定文本 DEBUGPY_READY。
#
# tasks.json 用 DEBUGPY_READY 作为 problemMatcher.background.endsPattern，判断
# 何时可以让 launch.json 的调试配置 attach 上来。之所以主动探测端口而不是依赖
# debugpy 自身的启动日志，是因为不同版本的 debugpy 在 --wait-for-client 模式下
# 是否打印、打印什么样的“正在监听”文本并不稳定，直接探测端口更可靠。
#
# 探测就绪状态时只读取本机内核的监听状态（Linux 读 /proc/net/tcp[6]，macOS 用
# lsof 查询），不会真正发起一次 TCP 连接：实测发现哪怕只是连接后立刻断开、不发
# 送任何数据，debugpy 的 --wait-for-client 也会把这次连接当作一次真实客户端
# attach 并随后退出监听，导致 VS Code 之后再连接时端口已经消失。
#
# 实际持有监听 socket 的是 debugpy 自行派生、随后与本脚本脱离父子关系的 adapter
# 进程（无法再通过进程树把它和本脚本启动的 debugpy 关联起来），所以无法靠 PID
# 归属来判断这个监听是不是本次启动的。因此改为在启动前先确认端口尚未被占用（占
# 用多半是上一次会话残留的孤儿进程，直接报错让用户清理，而不是静默复用）；有这
# 个前置条件后，轮询期间只要观察到端口进入监听状态，就必然是本次启动的进程，因
# 为同一端口不可能同时被两个监听者占用。
#
# 用法:
#   scripts/debugpy_listen.sh <solution.py 路径> <用例输入文件路径> [端口，默认 5678]
#
# 依赖:
#   运行题目脚本的 Python 环境需要能 `python3 -m debugpy`（先 `pip install
#   debugpy`）。这与 VS Code Python 扩展自带、用于普通 "launch" 调试的 debugpy
#   是两回事：这里用命令行方式手动发起监听以便重定向 stdin，因此需要环境里能直
#   接导入 debugpy。

set -uo pipefail

PYTHON_BIN="${PYTHON_BIN:-python3}"

if [[ $# -lt 2 ]]; then
    echo "用法: $0 <solution.py 路径> <用例输入文件路径> [端口]" >&2
    exit 2
fi

solution_path="$1"
input_file="$2"
port="${3:-5678}"

if [[ ! -f "$solution_path" ]]; then
    echo "错误: 未找到解答文件 $solution_path" >&2
    exit 2
fi

if [[ ! -f "$input_file" ]]; then
    echo "错误: 未找到测试用例输入 $input_file" >&2
    exit 2
fi

if ! command -v "$PYTHON_BIN" >/dev/null 2>&1; then
    echo "错误: 未找到 Python 解释器 $PYTHON_BIN，请先运行 scripts/setup.sh 完成环境初始化。" >&2
    exit 2
fi

os_name=$(uname -s)

port_has_listener() {
    case "$os_name" in
        Darwin)
            lsof -nP -iTCP:"$port" -sTCP:LISTEN >/dev/null 2>&1
            ;;
        *)
            local port_hex
            port_hex=$(printf '%04X' "$port")
            awk -v want="$port_hex" '
                FNR > 1 {
                    split($2, addr, ":")
                    if (addr[2] == want && $4 == "0A") { found = 1 }
                }
                END { exit !found }
            ' /proc/net/tcp /proc/net/tcp6 2>/dev/null
            ;;
    esac
}

if port_has_listener; then
    echo "错误: 端口 $port 已被占用（可能是上一次调试会话遗留的孤儿进程），请先结束占用该端口的进程后重试，或更换调试配置中使用的端口。" >&2
    exit 2
fi

"$PYTHON_BIN" -m debugpy --listen "$port" --wait-for-client "$solution_path" < "$input_file" &
debugpy_pid=$!
# VS Code 取消调试/终止后台任务时会给本脚本发信号；如果不主动杀掉子进程，
# debugpy 会成为孤儿进程继续占用端口，导致下一次 F5 探测端口失败。取消/终止是
# 用户主动发起的，必须让脚本立刻退出，而不是继续走到下面“未能进入监听状态”的
# 错误分支（那是为真正的启动失败保留的）。
cleanup() { kill "$debugpy_pid" 2>/dev/null; }
trap cleanup EXIT
trap 'cleanup; exit 130' INT
trap 'cleanup; exit 143' TERM

ready=0
for _ in $(seq 1 100); do
    if ! kill -0 "$debugpy_pid" 2>/dev/null; then
        break
    fi
    if port_has_listener; then
        ready=1
        break
    fi
    sleep 0.1
done

if [[ $ready -eq 1 ]]; then
    echo "DEBUGPY_READY"
else
    echo "错误: debugpy 未能在 $port 端口上进入监听状态（可能未安装 debugpy，或脚本本身启动失败）。" >&2
    # debugpy 在 --wait-for-client 模式下如果一直没有客户端 attach 不会自行退出，
    # 必须先杀掉它，否则下面的 wait 会永久阻塞，脚本无法以失败退出。
    kill "$debugpy_pid" 2>/dev/null
    wait "$debugpy_pid" 2>/dev/null
    exit 2
fi

wait "$debugpy_pid"
exit $?
