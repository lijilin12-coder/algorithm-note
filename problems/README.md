# 题目目录约定

每道题目是 `problems/<分类>/<题目名>/` 下的一个独立目录，包含：

```
problems/<分类>/<题目名>/
  problem.md       # 题目描述
  solution.cpp      # C++ 解答
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
- 新增题目时只需按以上结构创建目录和文件，无需修改 `scripts/run_tests.sh`。

## 运行测试

```bash
scripts/run_tests.sh problems/examples/a-plus-b
```

比较时忽略行尾空白和空行差异（`diff -b -B`），聚焦于实际内容是否一致。

传入的目录如果不直接包含 `solution.cpp`（如 `problems/examples`、`problems`），
会自动按批量模式运行：递归发现该目录下所有题目（不限层级），依次运行，任意一个
题目失败即停止。

## 复用共享代码

编译 `solution.cpp` 时已统一加入 `-I <仓库根>/common`，题目中可直接用
`#include "linked_list.h"` 等方式引用 [common/](../common/) 下的共享头文件，无需
重复实现常用数据结构/工具函数。
