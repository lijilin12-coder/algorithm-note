// 提示：使用C++ 的 cout 输出 "Hello, World!"，并在末尾换行。
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
// void swap(int  a, int b)     // 值传递
// void swap(int* a, int* b)   //指针传递
// int b,c;
// int& a = b;
// int& a = c;
// 引用只能绑定一个变量，而且一旦创建，必须绑定，不能有空引用。
// 引用用法和变量一样，不需要解引用。

void swap(int* a, int* b)   //指针传递
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap(int& a, int& b)   //引用传递
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    double pi = 3.14159265;
    printf("Helloworld! %d\n", 2026);
    printf("日期：%d-%d-%d\n", 2026, 8,31);
    cout << pi << endl;
    cout << fixed << setprecision(4) << pi << endl;
    std::cout << "日期：" << 2026 <<" - "<< 8 << "-"<< 31 <<"Pi = " << pi<<"\n";

    // char name[512];
    // int age;

    // scanf("%s %d", name, &age);
    // printf("Name: %s \t age: %d\n", name, age);

    // string name;
    // int age;

    // cin >> name >> age;
    // cout << "Name: " << name << "\t" << "Age: " << age << endl;

    // string greeting;
    // // cin >> greeting;
    // getline(cin, greeting);
    // cout << "Echo " << greeting << endl;

    int a,b,c;
    // vector<int> vec(15, -1); // 初始化
    // cout << "vec.empty: " << vec.empty() << endl;
    // cout << "vec.size: " << vec.size() << endl;

    vector<vector<int>> matrix;
    while(cin >> a >> b>>c)
    {
        // cout << a <<" " << b << " " << c << endl;
        // swap(a, b);
        // cout << a <<" " << b << " " << c << endl;
        // cout << "-----\n";
        vector<int> vec;
        vec.push_back(a);
        // vec.pop_back();
        vec.push_back(b);
        vec.push_back(c);
        matrix.push_back(vec);
    }

    //数组
    for(int row = 0; row < matrix.size(); row++)
    {
        vector<int> rows = matrix[row];
        for(int col = 0; col < rows.size(); ++col)
        {
            cout << matrix[row][col] << " " ;
        }
        cout << endl;
    }

    // 迭代器
    // for(auto it = matrix.begin(); it!=matrix.end(); ++it)
    // {
    //     for(auto row_it = it->begin(); row_it!=it->end(); ++row_it)
    //     {
    //         cout << *row_it << " ";
    //     }
    //     cout << endl;
    // }

    // for-each
    // for(auto row : matrix)
    // {
    //     for(auto item : row)
    //     {
    //         cout << item << " ";
    //     }
    //     cout << endl;
    // }
    return 0 ;
}