# A brief introduction
Algorithms-node is a personal note project that notes down the common algorithms and data structures that I've learned.

# 算法本地学习平台

本仓库同时包含一个本地刷题验证平台，用于弥补在线 OJ 缺少免费本地调试能力的问题。

## 快速开始

1. 初始化环境（首次使用，自动检测并安装 C++ 编译器）：

   ```bash
   scripts/setup.sh
   ```

2. 运行示例题目验证环境是否可用：

   ```bash
   scripts/run_tests.sh problems/examples/a-plus-b
   ```

支持环境：macOS（通过 Homebrew）、WSL/Linux（通过 apt）与 Windows（Git Bash，通过 winget）。

### Windows（Git Bash）

1. 安装 [Git for Windows](https://git-scm.com/download/win)，之后的所有命令都在
   **Git Bash** 中执行（不支持 PowerShell / cmd）。
2. 确认系统自带 `winget` 可用（Windows 10/11 的“应用安装程序”，可从 Microsoft Store
   更新）。
3. 运行 `scripts/setup.sh`：缺少编译器时通过 winget 安装 MSYS2，并在其中安装
   MinGW-w64 的 g++ 与 gdb；缺少 Python 时通过 winget 安装 Python。脚本会自动把
   `C:\msys64\ucrt64\bin` 追加到 Windows 用户环境变量 `PATH`（已存在则跳过；失败时
   会提示手动添加的方法）。
4. 重新打开 Git Bash 和 VS Code，使新的 `PATH` 生效。

如果仓库是在添加 `.gitattributes` 之前就已在 Windows 上克隆的，先执行一次
`git rm -r --cached -q . && git reset --hard`，把脚本和测试用例重新检出为 LF 行尾。

之后 `scripts/run_tests.sh` 的用法与其他平台完全相同。Windows 上没有 `python3`
时会自动改用 `python`（也可以用 `PYTHON_BIN` 环境变量指定）；程序输出为 CRLF
行尾不影响判题。`scripts/debug.sh` 命令行调试暂不支持 Windows，请使用下方的
VS Code 图形化调试。

## 批量测试

`scripts/run_tests.sh` 传入的目录如果本身不是题目目录（不直接包含
`solution.cpp`），会自动按批量模式运行：递归发现该目录下所有题目（不限层级），
按路径排序依次编译并测试，某个题目失败时跳过并继续运行后续题目，最后汇总输出所有
失败的题目。

```bash
scripts/run_tests.sh problems/examples   # 运行 examples 分类下所有题目
scripts/run_tests.sh problems            # 运行全部题目
```

## 共享代码

常用数据结构/工具以仅头文件形式存放在 [common/](common/) 目录（如 `common/linked_list.h`），
编译时已统一注入 `-I common`，题目 `solution.cpp` 中可直接 `#include "linked_list.h"`
引用，无需关心题目目录的嵌套深度，也无需重复实现。新增共享代码时在 `common/` 下按
同样方式添加头文件即可（如未来的 `tree.h`、`graph.h`）。

## 新增题目

按 [problems/README.md](problems/README.md) 中的目录约定创建题目目录即可，无需修改测试框架代码。

## 调试

- **命令行调试**（gdb / lldb）：

  ```bash
  scripts/debug.sh problems/examples/a-plus-b 1
  ```

  WSL/Linux 下自动进入 gdb，macOS 下自动进入 lldb；启动后按提示设置断点并运行。
  （Windows 暂不支持，请使用 VS Code 图形化调试。）

- **VS Code 图形化调试**：打开你要调试的题目的 `solution.cpp`（确保它是当前激活
  的编辑器标签页），设置断点后按 F5 启动即可，调试目标会自动对应到该题目所在文件
  夹，无需手动修改 [.vscode/launch.json](.vscode/launch.json)。
  WSL/Linux 选择 "Debug (Linux/WSL - gdb)"，macOS 选择 "Debug (macOS - lldb)"，
  Windows 选择 "Debug (Windows - gdb)"。Windows 上 Python 题目的调试任务通过
  Git Bash 运行，要求 Git for Windows 安装在默认路径
  `C:\Program Files\Git`（否则修改 `.vscode/tasks.json` 中的 bash 路径）。
  默认使用该题目的 `tests/1.in` 作为输入；如需调试其他用例，手动修改
  `launch.json` 中的用例编号（如把 `tests/1.in` 改成 `tests/2.in`）。

## 框架自测

```bash
tests/run_framework_tests.sh
```

