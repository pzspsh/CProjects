/*
@File   : test2.c
@Author : pan
@Time   : 2023-12-06 19:50:09
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main()
{
    int m, n;
    int p = 1;
    scanf("%d%d", &m, &n);
    for (int i = 0; m + i <= n; i++)
    {
        int a = m + i;
        int sum = 0;
        do
        {
            int b = 0;
            b = a % 10;
            sum = sum + b * b * b;
            a = a / 10;
        } while (a != 0);
        if (sum == m + i && p == 1)
        {
            p = 0;
            printf("%d ", m + i);
        }
        else if (sum == m + i && p == 0)
        {
            printf(" %d", m + i);
        }
    }
    printf("aaa:%d", p);
    return 0;
}