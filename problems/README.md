# 题目目录约定

每道题目是 `problems/<分类>/<题目名>/` 下的一个独立目录，包含：

```
problems/<分类>/<题目名>/
  problem.md       # 题目描述
  solution.cpp      # C++ 解答，或
  solution.py        # Python 解答（二选一，不能同时存在）
  tests/
    1.in            # 第 1 组测试的输入
    1.ans           # 第 1 组测试的期望输出
    2.in
    2.ans
    ...
```

- 分类目录（如 `examples`、`dp`、`graph`）按知识点组织，可自由新增。
- 测试用例文件按编号成对出现：`<编号>.in` 对应 `<编号>.ans`。编号不要求连续。
- 期望输出使用 `.ans` 扩展名，而不是 `.out`（`.out` 已被仓库 `.gitignore` 忽略，用于
  编译产物）。
- 一道题目只能选择一种语言：目录下放 `solution.cpp` 或 `solution.py` 其中之一。
  如果两个文件同时存在，`scripts/run_tests.sh` 与 `scripts/debug.sh` 会明确报错，
  不会静默选择其中一种运行。
- 新增题目时只需按以上结构创建目录和文件，无需修改 `scripts/run_tests.sh`。

## 运行测试

```bash
scripts/run_tests.sh problems/examples/a-plus-b
```

比较时忽略行尾空白和空行差异（`diff -b -B`），聚焦于实际内容是否一致。

传入的目录如果不直接包含解答文件（`solution.cpp` 或 `solution.py`，如
`problems/examples`、`problems`），会自动按批量模式运行：递归发现该目录下所有
题目（不限层级），依次运行，某个题目失败时跳过并继续运行后续题目，最后汇总输出
所有失败的题目。C++ 题目与 Python 题目可以混在同一批次里，各自按自己的语言运行。

Python 题目（`solution.py`）不需要编译步骤，直接用 `python3` 运行；解释器名称可
通过 `PYTHON_BIN` 环境变量覆盖（默认 `python3`），与 C++ 的 `CXX` 环境变量用法一致。

## 复用共享代码

编译 `solution.cpp` 时已统一加入 `-I <仓库根>/common`，题目中可直接用
`#include "linked_list.h"` 等方式引用 [common/](../common/) 下的共享头文件，无需
重复实现常用数据结构/工具函数。目前提供：

- `linked_list.h`：单链表。
- `tree.h`：二叉树（LeetCode 风格节点 + 按层序 token 建树/释放，遍历由题目自
  己实现）。
- `nary_tree.h`：N 叉树（LeetCode 风格节点 + 按层序 token 建树/释放，遍历由
  题目自己实现）。
- `queue.h`：链表实现的队列（FIFO），常用于层序遍历（BFS）。
- `stack.h`：链表实现的栈（LIFO），常用于迭代式 DFS。

以上共享头文件目前只提供给 C++ 题目使用；`solution.py` 暂时没有对应的共享模块，
需要时各题自行实现。
