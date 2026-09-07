#include <stdio.h>
int main()
{
    int a, b, c;
    int d, e, f;

    printf("请输入出生时间（年月日）");
    scanf("%d %d %d", &a, &b, &c);

    printf("您想查询的日期（年月日）");
    scanf("%d %d %d", &d, &e, &f);

    int t1 = a * 365 + b * 30 + c;
    int t2 = d * 365 + e * 30 + f;

    int t = t2 - t1;

    printf("您在这时已经降生%d(年)%d(月)%d(日)", t / 365, (t % 365) / 30, t % 365 % 30);

    return 0;
}
