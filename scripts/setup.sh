#!/usr/bin/env bash
# 一键初始化本地开发环境：检测操作系统并安装/校验 C++ 编译器。
#
# 支持:
#   - macOS（通过 Homebrew 安装 gcc）
#   - WSL / Linux（通过 apt 安装 build-essential）
#
# 用法:
#   scripts/setup.sh

set -uo pipefail

CXX="${CXX:-g++}"

check_compiler() {
    if command -v "$CXX" >/dev/null 2>&1; then
        echo "已找到编译器: $("$CXX" --version | head -1)"
        return 0
    fi
    return 1
}

os_name=$(uname -s)
echo "检测到操作系统: $os_name"

case "$os_name" in
    Darwin)
        if check_compiler; then
            :
        else
            if ! command -v brew >/dev/null 2>&1; then
                echo "错误: 未检测到 Homebrew，请先按 https://brew.sh 安装后重试。" >&2
                exit 1
            fi
            echo "正在通过 Homebrew 安装 gcc ..."
            if ! brew install gcc; then
                echo "错误: brew install gcc 失败，请查看上方输出。" >&2
                exit 1
            fi
        fi
        ;;
    Linux)
        if check_compiler; then
            :
        else
            if command -v apt-get >/dev/null 2>&1; then
                echo "正在通过 apt 安装 build-essential（可能需要输入密码）..."
                if ! sudo apt-get update || ! sudo apt-get install -y build-essential; then
                    echo "错误: apt-get 安装失败，请查看上方输出。" >&2
                    exit 1
                fi
            else
                echo "错误: 未检测到 apt-get，请手动安装 g++ 后重试。" >&2
                exit 1
            fi
        fi
        ;;
    *)
        echo "错误: 暂不支持的操作系统: $os_name" >&2
        exit 1
        ;;
esac

if check_compiler; then
    echo ""
    echo "环境初始化完成，可运行示例题目验证："
    echo "  scripts/run_tests.sh problems/examples/a-plus-b"
else
    echo "错误: 编译器安装流程已执行，但仍未检测到 $CXX，请手动检查安装。" >&2
    exit 1
fi
