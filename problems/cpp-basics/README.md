# C++ 基础入门123
## 1. 输入输出

### 1.1 hello, world!

```cpp
#include <iostream>      // 引入输入输出库
using namespace std;     // 使用标准命名空间

int main()
{
    cout << "Hello, World!" <<endl;  //endl 表示换行
    return 0;
}
```

### 1.2 输出数据

```cpp
#include <iostream>
using namespace std;

int main() {
    // 输出字符串，endl 换行
    // 输出：Hello
    cout << "Hello" << endl;

    // 输出整数
    int age = 25;
    // 输出：年龄是 25
    cout << "年龄是 " << age << endl;

    // 输出浮点数
    double pi = 3.14159;
    // 输出：pi = 3.14159
    cout << "pi = " << pi << endl;

    // 链式输出：用多个 << 连接
    int x = 10, y = 20;
    // 输出：x = 10, y = 20
    cout << "x = " << x << ", y = " << y << endl;

    // 输出单个字符
    char c = 'A';
    // 输出：字符：A
    cout << "字符：" << c << endl;

    return 0;
}
```

cout 比 C 语言的 printf 方便的地方在于不用记格式化占位符（%d、%f 之类的），直接用 << 把变量丢进去就行，编译器会自动根据类型来输出。

endl 和 "\n" 都能换行，区别是 endl 会多一步刷新缓冲区的操作。在算法题中大量输出时，用 "\n" 会比 endl 快一些，不过一般不用太在意。

如果想控制浮点数的小数位数，需要引入 <iomanip> 头文件：

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.14159265;

    // 默认输出
    // 输出：3.14159
    cout << pi << endl;

    // fixed + setprecision 控制小数位数
    // 输出：3.14
    cout << fixed << setprecision(2) << pi << endl;

    // 输出：3.1416（四舍五入到 4 位小数）
    cout << fixed << setprecision(4) << pi << endl;

    return 0;
}
```

### 1.3 读取输入cin

cin 配合 >> 运算符（提取运算符）来读取输入：
```cpp
#include <iostream>
using namespace std;

int main() {
    string name;
    int age;

    // 读取一个字符串和一个整数
    cin >> name >> age;

    // 输出：姓名：Alice
    cout << "姓名：" << name << endl;
    // 输出：年龄：25
    cout << "年龄：" << age << endl;

    return 0;
}
```

### 1.4 读取整行

如果需要读取一整行（包括空格），可以用 getline：
```cpp
#include <iostream>
using namespace std;

int main() {
    string line;
    // 读取一整行（包括空格）
    getline(cin, line);
    // 输出：How are you?
    cout << line << endl;
    return 0;
}
```

### 1.5 读取多行直到结束
有些题目的输入数据量不确定，需要一直读取到输入结束（EOF）。把 cin >> 放到 while 的条件中就行

```cpp
#include <iostream>
using namespace std;

int main() {
    // 不断读取整数，直到输入结束
    int x;
    while (cin >> x) {
        cout << x << "\n";
    }
    return 0;
}
```
## 2.引用、常量指针、指针常量

1. 为什么要有常量指针、指针常量

```cpp
void print_linked_list(const Node* const head)
{
    // 这里的head 会又被修改的风险，用 const是一种更保险的操作
    for(Node* p = head->next; p; p=p->next)
    {
        printf("%d ", p->val);
    }
    printf("\n");
}
```

## 3. 从数组到 vector

### 3.1 原始数组的局限

C 风格数组在刷题时有两个明显的痛点：

```cpp
int a[5];       // 大小必须在编译期就写死，运行时不能改
int n;
cin >> n;
int b[n];       // 有些编译器支持变长数组，但这不是标准 C++ 的写法，不要依赖它

int cnt = 0;
int c[100];
int x;
while (cin >> x) {
    c[cnt++] = x;   // 数组开多大全靠猜，猜小了就会越界写坏内存
}
```

- **大小固定**：数组一旦声明，长度就不能再变，遇到"不知道有多少个数"的题目
  只能预先开一个足够大的数组，既浪费空间又可能猜错。
- **没有长度信息**：数组本身不知道自己存了多少个有效元素，必须额外用一个变量
  （如上面的 `cnt`）来记录，写多了容易漏更新、越界。

`vector`（`#include <vector>`）就是为了解决这两个问题：它是一个可以动态增长的
数组，自己记录当前元素个数，用起来和数组几乎一样，但更安全、更省心。

### 3.2 声明与初始化

```cpp
#include <vector>
using namespace std;

int main() {
    vector<int> a;                    // 空 vector，长度为 0
    vector<int> b(5);                 // 5 个元素，默认初始化为 0
    vector<int> c(5, -1);             // 5 个元素，都初始化为 -1
    vector<int> d = {1, 2, 3, 4, 5};  // 列表初始化

    // 二维 vector：3 行 4 列，元素都初始化为 0（对应数组里的 int grid[3][4]）
    vector<vector<int>> grid(3, vector<int>(4, 0));
}
```

### 3.3 增删元素：数组做不到的动态扩容

```cpp
vector<int> v;

v.push_back(10);   // 尾部添加元素：[10]
v.push_back(20);   // [10, 20]
v.pop_back();       // 删除末尾元素：[10]

cout << v.size() << endl;    // 元素个数：1（数组需要自己额外维护这个值）
cout << v.empty() << endl;   // 是否为空：0（false）
```

`pop_back` 只能删除末尾元素，如果要删除中间的某个元素，要用 `erase`。`erase`
需要传入迭代器（用法在 3.5 详细解释，这里先知道 `v.begin() + i` 表示第 `i` 个
位置即可）：

```cpp
vector<int> v = {1, 2, 3, 4, 5};

v.erase(v.begin() + 1);        // 删除下标 1 的元素（值为 2）：[1, 3, 4, 5]
v.erase(v.begin(), v.begin() + 2); // 删除区间 [0, 2)，即前两个元素：[4, 5]
```

`erase` 会把被删除位置之后的元素依次往前移动，删除一个元素的时间复杂度是
`O(n)`，比只删末尾的 `pop_back`（`O(1)`）慢很多。刷题时如果只需要删除末尾元素，
优先用 `pop_back`；只有确实要删除中间元素时才用 `erase`。

**`erase` 之后旧迭代器会失效**：调用 `erase` 之后，指向被删除位置及其之后的
所有迭代器都会失效，继续用它们（哪怕只是 `++it`）都是未定义行为，运行时可能
崩溃，也可能不报错但结果不对——这正是“erase 后再访问出错”最常见的原因。典型的
错误写法和正确写法：

```cpp
vector<int> v = {1, 2, 3, 2, 5};

// 错误写法：erase 之后 it 已经失效，for 循环里的 ++it 是未定义行为
for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it == 2) {
        v.erase(it); // it 失效了，下一次 ++it 可能崩溃或跳过元素
    }
}

// 正确写法：erase 会返回指向下一个有效元素的迭代器，用它来更新 it
for (auto it = v.begin(); it != v.end(); ) {
    if (*it == 2) {
        it = v.erase(it); // 用返回值更新 it，不再手动 ++it
    } else {
        ++it;
    }
}
```

**其他删除方式**：

```cpp
vector<int> v = {1, 2, 3, 2, 5};

v.clear();   // 删除所有元素，之后 v.size() == 0

// remove-erase 写法：一次性删除所有等于某个值的元素
// remove 只是把要留下的元素移到前面，返回“新末尾”的位置，本身不改变 size()，
// 真正的删除还是要交给 erase
v.erase(remove(v.begin(), v.end(), 2), v.end()); // 删除所有值为 2 的元素
```

### 3.4 访问与遍历：和数组几乎一样

```cpp
vector<int> v = {1, 2, 3, 4, 5};

v[0] = 100;    // 下标访问/修改，和数组用法相同，越界不会报错，行为未定义
v.at(0) = 100; // at 访问，越界会抛异常，更安全但稍慢

// 下标遍历
for (int i = 0; i < (int)v.size(); i++) {
    cout << v[i] << " ";
}
cout << endl;

// 范围 for（C++11），更简洁
for (int x : v) {
    cout << x << " ";
}
cout << endl;

// 范围 for + 引用，可以直接修改元素
for (int &x : v) {
    x *= 2;
}

// 迭代器遍历，写法介于下标和范围 for 之间，3.5 会解释 it 是什么
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
cout << endl;
```

`v.size()` 返回的是无符号整数类型 `size_t`，如果拿它和负数比较，或者用两个
`size()` 相减，很容易得到意外的结果（比如变成一个很大的正数）。写循环时注意加上
`(int)` 强转，或者直接用范围 for 避免这个坑。

### 3.5 迭代器：算法函数为什么要传 `begin()`/`end()`

前面遍历用的是下标或范围 for，但后面 3.7 的算法函数（`sort`、`find` 等）都是
传 `v.begin()`、`v.end()` 这样的“迭代器”，而不是直接传 `v`，这里先解释一下。

迭代器可以理解成一种“广义指针”：它指向容器里的某个元素，可以用 `*it` 取出
指向的值，用 `++it` 移动到下一个位置。

```cpp
vector<int> v = {1, 2, 3, 4, 5};

vector<int>::iterator it = v.begin(); // 指向第一个元素
cout << *it << endl;                   // 1

it++;               // 移动到下一个元素
cout << *it << endl; // 2
```

3.4 最后一个例子用 `for (auto it = v.begin(); it != v.end(); ++it)` 遍历了整个
vector：每次循环 `++it` 移动到下一个位置，`*it` 取出当前指向的值，直到 `it`
等于 `v.end()` 时停止。

- `v.begin()` 指向第一个元素；`v.end()` 指向“最后一个元素之后”的位置，本身
  不指向任何有效元素，只用来判断遍历有没有结束，不能对它解引用（`*v.end()`）。
- `vector` 的迭代器支持随机访问，两个迭代器相减能算出下标：`it - v.begin()`
  就是 `it` 指向元素的下标，3.7 的 `find` 例子里用到过这个写法。
- 算法函数统一要求传迭代器而不是容器本身，是因为同一套 `sort`、`find` 逻辑
  这样就能复用在 `vector`、`list`、`set` 等不同容器上，不用为每种容器单独写一份。
- 实际写代码时一般不用写出 `vector<int>::iterator` 这么长的类型名，直接用
  `auto it = v.begin();` 让编译器自动推导即可。

### 3.6 用 vector 解决“不知道要读多少个数”

回到 3.1 的问题：有了 `push_back`，就不用再预先猜数组大小、手动维护计数器了，
用 `while (cin >> x)` 一直读到输入结束（EOF）即可：

```cpp
vector<int> v;
int x;
while (cin >> x) {
    v.push_back(x);
}
```

### 3.7 配合 `<algorithm>` 的常用算法函数

vector 的另一个好处是能直接配合标准库算法使用，不用自己手写排序、查找这些逻辑。
常用的按功能分为三类：

**排序 / 反转**

```cpp
#include <algorithm>

vector<int> v = {5, 3, 1, 4, 2};

sort(v.begin(), v.end());                  // 升序排序：1 2 3 4 5
sort(v.begin(), v.end(), greater<int>());  // 降序排序：5 4 3 2 1

reverse(v.begin(), v.end());               // 原地反转
```

**求和 / 求最值**

```cpp
#include <numeric>   // accumulate

int sum = accumulate(v.begin(), v.end(), 0); // 求和，0 是累加的初始值

auto maxIt = max_element(v.begin(), v.end()); // 指向最大值的迭代器
auto minIt = min_element(v.begin(), v.end()); // 指向最小值的迭代器
cout << *maxIt << " " << *minIt << endl;      // 用 * 取出迭代器指向的值
```

**查找 / 计数**

```cpp
auto it = find(v.begin(), v.end(), 3);  // 查找第一个等于 3 的元素
if (it != v.end()) {
    cout << "找到了，位置：" << it - v.begin() << endl;
}

int cnt = count(v.begin(), v.end(), 3); // 统计元素 3 出现的次数
```

### 3.8 小结

| 分类 | 需求 | 写法 |
| --- | --- | --- |
| 声明 | 固定长度 / 指定初始值 | `vector<int> b(5)` / `vector<int> c(5, -1)` |
| 增删 | 尾部添加 / 删除 | `v.push_back(x)` / `v.pop_back()` |
| 删除 | 删除指定位置 / 删除区间 / 清空 / 删除所有等于某值的元素 | `v.erase(v.begin() + i)` / `v.erase(v.begin(), v.begin() + k)` / `v.clear()` / `v.erase(remove(v.begin(), v.end(), x), v.end())` |
| 大小 | 元素个数 / 是否为空 | `v.size()` / `v.empty()` |
| 访问 | 读写单个元素 | `v[i]` 或 `v.at(i)` |
| 迭代器 | 起止位置 / 取值 / 移动 | `v.begin()` / `v.end()` / `*it` / `++it` |
| 排序 | 升序 / 降序 / 反转 | `sort(v.begin(), v.end())` / `sort(v.begin(), v.end(), greater<int>())` / `reverse(v.begin(), v.end())` |
| 统计 | 求和 / 最大最小值 | `accumulate(...)` / `*max_element(...)` / `*min_element(...)` |
| 查找 | 查找元素 / 统计出现次数 | `find(v.begin(), v.end(), x)` / `count(v.begin(), v.end(), x)` |

### 练习

- [4vector-sum-max](4vector-sum-max/problem.md)：读入 n 个整数，输出它们的和与最大值。
- [5vector-reverse](5vector-reverse/problem.md)：读入 n 个整数，逆序输出。
- [6vector-sort](6vector-sort/problem.md)：读入若干整数直到输入结束，排序后输出。
- [7vector-erase-value](7vector-erase-value/problem.md)：删除 vector 中所有等于某个值的元素。
- [8vector-find-index](8vector-find-index/problem.md)：用 find 查找元素第一次出现的下标。

## 4. 字符串 string

`string`（`#include <string>`）是 C++ 标准库提供的字符串类型，用起来和
`vector<char>` 很像：支持动态扩容、下标访问、迭代器遍历，还额外提供了拼接、
比较、子串、查找等专门针对字符串的操作。

### 4.1 声明与初始化

```cpp
#include <string>
using namespace std;

int main() {
    string a;                  // 空字符串
    string b = "hello";        // 直接用字符串字面量初始化
    string c(5, 'x');          // 5 个 'x'："xxxxx"
    string d = b;              // 拷贝初始化
}
```

### 4.2 拼接与比较

```cpp
string a = "hello", b = "world";

string c = a + " " + b;   // 拼接："hello world"
a += "!";                  // 追加："hello!"

// 字符串比较是按字典序逐个字符比较，可以直接用关系运算符
cout << (a == "hello!") << endl;  // 1（true）
cout << (string("abc") < "abd") << endl;  // 1（true，第三个字符 c < d）
```

### 4.3 常用方法：长度、下标、子串、查找

```cpp
string s = "Hello, World!";

s.size();               // 13，和 s.length() 完全一样
s[0];                    // 'H'，下标访问单个字符

s.substr(0, 5);          // "Hello"：substr(起始位置, 长度)
s.substr(7);             // "World!"：省略长度表示截到末尾

s.find("World");         // 7：首次出现的下标
s.find("xyz");           // 找不到，返回 string::npos
```

`find` 找不到时返回的是 `string::npos`，不是 `-1`。虽然 `npos` 的值通常等于
`-1` 的无符号表示，但最好用 `string::npos` 来判断，这是标准写法：

```cpp
if (s.find("xyz") == string::npos) {
    cout << "not found" << endl;
}
```

### 4.4 字符串与数字转换

```cpp
#include <string>

int n = stoi("123");                     // 字符串转 int：123
long long big = stoll("1234567890123");  // 字符串转 long long

string s1 = to_string(42);   // 数字转字符串："42"
string s2 = to_string(3.14); // "3.140000"（浮点数默认 6 位小数）
```

### 4.5 字符判断与转换

`<cctype>` 提供了一组判断和转换单个字符的函数，在处理字符串的算法题中经常
用到：

```cpp
#include <cctype>

isdigit('3');   // 非 0（true），是不是数字字符 '0'-'9'
isalpha('a');   // 非 0（true），是不是字母

(char)toupper('a');  // 'A'
(char)tolower('A');  // 'a'
```

`isdigit`/`isalpha` 等函数的参数类型是 `int`，如果直接传 `char`（尤其是值为
负的字符），行为是未定义的，稳妥的写法是先转成 `unsigned char` 再传入：
`isdigit((unsigned char)c)`。

### 4.6 遍历

和 `vector` 一样，`string` 也支持下标遍历、范围 for、迭代器遍历，也能直接
传给 `sort`、`reverse` 等算法函数：

```cpp
string s = "hello";

reverse(s.begin(), s.end());  // "olleh"

for (char c : s) {
    cout << c;
}
```

### 4.7 小结

| 分类 | 需求 | 写法 |
| --- | --- | --- |
| 声明 | 空字符串 / 重复字符 | `string a` / `string c(5, 'x')` |
| 拼接 | 连接两个字符串 / 追加 | `a + b` / `a += b` |
| 比较 | 判断相等 / 字典序比较 | `a == b` / `a < b` |
| 长度 | 字符个数 | `s.size()` 或 `s.length()` |
| 访问 | 读写单个字符 | `s[i]` |
| 子串 | 截取子串 | `s.substr(pos, len)` |
| 查找 | 查找子串位置 | `s.find(t)`，找不到返回 `string::npos` |
| 转换 | 字符串转数字 / 数字转字符串 | `stoi(s)` / `stoll(s)` / `to_string(n)` |
| 字符判断 | 是否数字 / 是否字母 / 大小写转换 | `isdigit(c)` / `isalpha(c)` / `toupper(c)` / `tolower(c)` |
| 遍历 | 反转 / 逐字符遍历 | `reverse(s.begin(), s.end())` / `for (char c : s)` |

### 练习

- [9string-basic](9string-basic/problem.md)：字符串的拼接、长度和字典序比较。
- [10string-reverse](10string-reverse/problem.md)：反转字符串。
- [11string-substr-find](11string-substr-find/problem.md)：用 substr 截取子串，用 find 查找子串位置。
- [12string-num-convert](12string-num-convert/problem.md)：用 stoi 把字符串转成整数求和，再用 to_string 转回字符串。
- [13string-char-count](13string-char-count/problem.md)：用 isdigit/isalpha 统计字符串中数字字符和字母字符的个数。
