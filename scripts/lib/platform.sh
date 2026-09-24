# 供 scripts/ 下各脚本共用的平台差异处理：识别 Windows（Git Bash）环境、选择
# Python 解释器、确定可执行文件后缀，避免同一段平台判断在多个脚本里各写一份。
#
# 用 `source` 方式引入，不能独立执行。

# 当前是否运行在 Windows 的 Git Bash（MSYS2/MinGW/Cygwin 系）环境中。
is_windows_shell() {
    case "$(uname -s)" in
        MINGW*|MSYS*|CYGWIN*) return 0 ;;
        *) return 1 ;;
    esac
}

# 编译产物的可执行文件后缀：Windows 下为 .exe，其他平台为空。
exe_suffix() {
    if is_windows_shell; then
        printf '.exe'
    fi
}

# 确定 PYTHON_BIN：调用方已显式设置时原样使用；否则依次尝试 python3、python，
# 取第一个“能真正运行”的 Python 3 解释器。之所以要实际运行一次而不是只看
# command -v，是因为 Windows 自带的应用商店占位别名 python3.exe/python.exe 存在
# 于 PATH 中，但运行时只会打印安装提示并以非 0 退出；同时排除 python 指向
# Python 2 的旧系统。都不可用时保留 python3，由调用方沿用原有的“未找到 Python
# 解释器 python3”报错。只应在确实要用 Python 时调用（会实际启动一次解释器）。
resolve_python_bin() {
    if [[ -n "${PYTHON_BIN:-}" ]]; then
        return 0
    fi
    local candidate
    for candidate in python3 python; do
        if command -v "$candidate" >/dev/null 2>&1 && "$candidate" -c 'import sys; sys.exit(sys.version_info[0] < 3)' >/dev/null 2>&1; then
            PYTHON_BIN="$candidate"
            return 0
        fi
    done
    PYTHON_BIN=python3
}
