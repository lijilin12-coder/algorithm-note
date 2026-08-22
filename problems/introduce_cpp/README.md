# C++ 基础入门
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