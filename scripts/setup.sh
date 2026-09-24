#!/usr/bin/env bash
# 一键初始化本地开发环境：检测操作系统并安装/校验 C++ 编译器与 Python 解释器。
#
# 支持:
#   - macOS（通过 Homebrew 安装 gcc / python）
#   - WSL / Linux（通过 apt 安装 build-essential / python3）
#   - Windows Git Bash（通过 winget 安装 MSYS2 + MinGW-w64 g++/gdb 与 Python）
#
# 用法:
#   scripts/setup.sh

set -uo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
# is_windows_shell / resolve_python_bin：平台差异（Windows Git Bash）。
source "$script_dir/lib/platform.sh"

CXX="${CXX:-g++}"
# 记录用户是否显式指定了解释器：安装后刷新 PATH 时只对自动选择的解释器重新探测。
PYTHON_BIN_FROM_ENV="${PYTHON_BIN:-}"
resolve_python_bin

# Windows 下 winget 安装的默认位置（Git Bash 路径写法）。
MSYS2_ROOT="${MSYS2_ROOT:-/c/msys64}"
MINGW_BIN="$MSYS2_ROOT/ucrt64/bin"

check_compiler() {
    if command -v "$CXX" >/dev/null 2>&1; then
        echo "已找到编译器: $("$CXX" --version | head -1)"
        return 0
    fi
    return 1
}

check_python() {
    # 实际运行一次：Windows 应用商店的 python 占位别名能被 command -v 找到但无法运行。
    if command -v "$PYTHON_BIN" >/dev/null 2>&1 && "$PYTHON_BIN" -c 'import sys' >/dev/null 2>&1; then
        echo "已找到 Python 解释器: $("$PYTHON_BIN" --version 2>&1)"
        return 0
    fi
    return 1
}

# 刚通过 winget 安装的软件不会出现在当前终端的 PATH 里；把已知安装位置补进
# 本次会话的 PATH，并重新选择 Python 解释器，使安装后的检测能立即生效。
refresh_windows_path() {
    local dir
    [[ -d "$MINGW_BIN" ]] && PATH="$MINGW_BIN:$PATH"
    if [[ -n "${LOCALAPPDATA:-}" ]]; then
        for dir in "$(cygpath -u "$LOCALAPPDATA" 2>/dev/null)"/Programs/Python/Python3*; do
            [[ -d "$dir" ]] && PATH="$dir:$PATH"
        done
    fi
    export PATH
    if [[ -z "${PYTHON_BIN_FROM_ENV:-}" ]]; then
        unset PYTHON_BIN
        resolve_python_bin
    fi
}

install_windows_toolchain() {
    if ! command -v winget >/dev/null 2>&1; then
        echo "错误: 未检测到 winget（Windows 10/11 的“应用安装程序”自带）。请从 Microsoft Store 安装“应用安装程序”后重试，或手动安装：" >&2
        echo "  - C++ 编译器: 安装 MSYS2（https://www.msys2.org），在 MSYS2 终端执行 pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb，并把 C:\\msys64\\ucrt64\\bin 加入 PATH" >&2
        echo "  - Python: 从 https://www.python.org/downloads/windows/ 安装，勾选 “Add python.exe to PATH”" >&2
        return
    fi
    if ! check_compiler; then
        if [[ ! -x "$MSYS2_ROOT/usr/bin/bash.exe" ]]; then
            echo "正在通过 winget 安装 MSYS2 ..."
            winget install -e --id MSYS2.MSYS2 --accept-source-agreements --accept-package-agreements \
                || echo "错误: winget 安装 MSYS2 失败，请查看上方输出。" >&2
        fi
        if [[ -x "$MSYS2_ROOT/usr/bin/bash.exe" ]]; then
            # 从 Git Bash 启动 MSYS2 的 bash 会继承 MSYSTEM=MINGW64，显式指定
            # UCRT64 与上面的 MINGW_BIN 对应。全新安装的 MSYS2 包数据库是旧的，
            # 先同步升级一次（可能升级 MSYS2 核心后退出，所以与安装分成两步）。
            echo "正在通过 MSYS2 pacman 同步包数据库并安装 MinGW-w64 g++ 与 gdb ..."
            MSYSTEM=UCRT64 "$MSYS2_ROOT/usr/bin/bash.exe" -lc "pacman -Syu --noconfirm" || true
            MSYSTEM=UCRT64 "$MSYS2_ROOT/usr/bin/bash.exe" -lc "pacman -S --noconfirm --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb" \
                || echo "错误: pacman 安装 g++/gdb 失败，请查看上方输出。" >&2
        else
            echo "错误: 未在 $MSYS2_ROOT 找到 MSYS2，如安装在其他位置，请设置 MSYS2_ROOT 后重试。" >&2
        fi
    fi
    if ! check_python; then
        echo "正在通过 winget 安装 Python ..."
        # python.org 安装程序默认不把 python 加入 PATH，用 --override 显式要求。
        winget install -e --id Python.Python.3.12 --accept-source-agreements --accept-package-agreements \
            --override "/quiet InstallAllUsers=0 PrependPath=1" \
            || echo "错误: winget 安装 Python 失败，请查看上方输出。" >&2
    fi
    refresh_windows_path
    echo ""
    echo "提示: 请把 MinGW 目录加入 Windows 用户环境变量 PATH，然后重新打开 Git Bash / VS Code："
    echo "  $(cygpath -w "$MINGW_BIN" 2>/dev/null || echo "$MINGW_BIN")"
    echo "  （Python 安装程序会自动把 python 加入 PATH，同样需要重新打开终端后生效。）"
}

os_name=$(uname -s)
echo "检测到操作系统: $os_name"

case "$os_name" in
    Darwin)
        if ! check_compiler || ! check_python; then
            if ! command -v brew >/dev/null 2>&1; then
                echo "错误: 未检测到 Homebrew，请先按 https://brew.sh 安装后重试。" >&2
            else
                if ! check_compiler; then
                    echo "正在通过 Homebrew 安装 gcc ..."
                    brew install gcc || echo "错误: brew install gcc 失败，请查看上方输出。" >&2
                fi
                if ! check_python; then
                    echo "正在通过 Homebrew 安装 python ..."
                    brew install python || echo "错误: brew install python 失败，请查看上方输出。" >&2
                fi
            fi
        fi
        ;;
    Linux)
        if ! check_compiler || ! check_python; then
            if command -v apt-get >/dev/null 2>&1; then
                echo "正在更新 apt 软件包索引（可能需要输入密码）..."
                if sudo apt-get update; then
                    if ! check_compiler; then
                        echo "正在通过 apt 安装 build-essential ..."
                        sudo apt-get install -y build-essential || echo "错误: build-essential 安装失败，请查看上方输出。" >&2
                    fi
                    if ! check_python; then
                        echo "正在通过 apt 安装 python3 ..."
                        sudo apt-get install -y python3 || echo "错误: python3 安装失败，请查看上方输出。" >&2
                    fi
                else
                    echo "错误: apt-get update 失败，请查看上方输出。" >&2
                fi
            else
                echo "错误: 未检测到 apt-get，请手动安装缺失的 g++/python3 后重试。" >&2
            fi
        fi
        ;;
    MINGW*|MSYS*|CYGWIN*)
        if ! check_compiler || ! check_python; then
            install_windows_toolchain
        fi
        ;;
    *)
        echo "错误: 暂不支持的操作系统: $os_name" >&2
        exit 1
        ;;
esac

compiler_ready=0
python_ready=0
check_compiler && compiler_ready=1
check_python && python_ready=1

if [[ $compiler_ready -eq 0 ]]; then
    echo "错误: 仍未检测到编译器 $CXX，请手动检查安装。" >&2
fi

if [[ $python_ready -eq 0 ]]; then
    echo "错误: 仍未检测到 Python 解释器 $PYTHON_BIN，请手动检查安装。" >&2
fi

if [[ $compiler_ready -eq 0 || $python_ready -eq 0 ]]; then
    exit 1
fi

echo ""
echo "环境初始化完成，可运行示例题目验证："
echo "  scripts/run_tests.sh problems/examples/a-plus-b"
