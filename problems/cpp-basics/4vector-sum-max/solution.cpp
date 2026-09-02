#include <iostream>
using namespace std;
int main()
{
    int a, b;
    int i = 0;
    int max;
    int ret;
    cin >> a;
    while (i < a)
    {
        i++;
        cin >> b;
        if (i == 1)
        {
            max = b;
            ret = b;
        }
        else
        {
            ret += b;
            if (max < b)
            {
                max = b;
            }
        }
    }
    cout << ret << " " << max << endl;
    return 0;
}