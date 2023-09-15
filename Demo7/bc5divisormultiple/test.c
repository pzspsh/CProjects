/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 12:09:53
*/
#include <windows.h>
#include <stdio.h>
int gongyueshu(int a, int b)
{
    int c, d;
    c = a > b ? b : a;
    for (int i = 1; i <= c; i++)
    {
        if (a % i == 0 && b % i == 0)
            d = i;
    }
    return d;
}
int zuixiaogongbeishu(int a, int b)
{
    int c;
    c = a > b ? a : b;
    for (; 1; c++)
    {
        if (c % a == 0 && c % b == 0)
            break;
    }
    return c;
}
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int m, n;
    printf("输入两个数:");
    scanf("%d,%d", &m, &n);
    printf("最小公倍数为%d\n", zuixiaogongbeishu(m, n));
    printf("最大公约数为%d", gongyueshu(m, n));
}