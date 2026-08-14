# Outcome

`common/linked_list.h` 从 C++ 模板类改写为纯 C 风格（struct + 函数），更贴近数据
结构学习时的常见写法（如课堂/教材中手写链表的方式），同时仍可被 `solution.cpp`
（用 g++ 编译）正常引用。

# Scope

- 重写 `common/linked_list.h`：
  - 用 `typedef struct Node { int value; struct Node* next; } Node;` 定义节点
    （`value` 类型固定为 `int`，不再使用模板泛型，更贴近教材写法）。
  - 提供一组基础操作函数（`static inline`，避免头文件被多个源文件包含时的重复
    定义问题）：创建/初始化、尾部插入、按值查找、按值删除、遍历（返回长度或提供
    遍历回调）、释放整个链表。
  - 函数命名与实现风格贴近数据结构教材/课堂习惯（如 `list_create`、
    `list_push_back`、`list_find`、`list_remove`、`list_length`、`list_free`），
    并附中文注释解释每一步在做什么。
- 同步更新 `problems/examples/linked-list-basic/solution.cpp`，改用新的 C 风格
  API 完成同样的解题逻辑（求和），确保该示例题目继续通过。
- 更新 `common/linked_list.h` 顶部的用法示例注释，反映新的 C 风格调用方式。

# Non-goals

- 不新增双向链表、循环链表等其他链表变体，仅覆盖单链表。
- 不改动 `linked_list/linked_list.c`（仓库早期笔记文件，保持原样）。
- 不改动 `common/` 目录的引用机制（`-I common` 编译参数、`#include "linked_list.h"`
  引用方式不变）。
- 不新增其他共享头文件（如 `tree.h`、`graph.h`），仅限本次链表改写。
- 不要求支持任意类型（原模板的泛型能力放弃，固定为 `int`，更贴近入门学习场景；
  如后续需要其他类型可另开需求讨论）。

# Acceptance examples

- A1: 阅读 `common/linked_list.h`，确认链表节点与操作函数均为纯 C 风格（无
  `class`/`template`/`private` 等 C++ 专属语法），且每个函数有解释其数据结构操作
  意图的中文注释。
- A2: `scripts/run_tests.sh problems/examples/linked-list-basic` 使用改写后的 C
  风格 API 完成解答，编译并通过全部测试用例（行为与改写前一致：给定若干整数以 -1
  结尾，输出总和）。
- A3: 新增至少一个额外场景验证基础操作可用，例如查找与删除（可在示例题目或临时
  验证脚本中体现），确认 `list_find`/`list_remove` 等函数行为正确。
- A4: `scripts/run_tests.sh problems/examples`（批量模式）与
  `scripts/run_tests.sh problems`（全量）均全部通过，确认改写没有影响其他题目或
  批量流程。
- A5: `tests/run_framework_tests.sh` 框架自测无回归。

# Constraints and invariants

- 头文件必须保持仅头文件形式（`static inline` 函数），不新增需要单独编译链接的
  `.c`/`.cpp` 实现文件。
- 保留原有 include guard 宏名 `ALGORITHM_NOTE_COMMON_LINKED_LIST_H`。
- 用 g++（C++ 编译器）编译含有该头文件的 `solution.cpp` 时不能有编译警告/错误
  （`-Wall` 需通过）。
- `-I common` 的引用方式、`#include "linked_list.h"` 的引用路径不变。

# Decisions

- Q1: 主要用途 — 用户明确选择"题目复用用"：把 `common/linked_list.h` 从 C++
  模板改为纯 C 版本，供 `solution.cpp` 引用（而非改动 `linked_list/linked_list.c`
  笔记文件）。

# Open questions

（无）

# Verification expectations

- 实机运行 A2、A4 对应命令，确认编译与测试通过。
- 走读 `common/linked_list.h` 源码，确认 A1（纯 C 风格、无 C++ 专属语法、注释
  完整）与 A3（查找/删除等基础操作正确）。
- 运行 `tests/run_framework_tests.sh` 确认 A5 无回归。

