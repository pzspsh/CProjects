/*
@File   : test.c
@Author : pan
@Time   : 2023-11-23 19:16:51
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; m <= n; m = m + 1)
    {
        int b = m % 7;
        if (b == 0)
        {
            printf("%d is a multiple of 7\n", m);
        }
        int c = m;
        while (c != 0)
        {
            int d = c % 10;
            if (d == 7)
            {
                printf("%d contains 7\n", m);
                break;
            }
            else
            {
                c = c / 10;
            }
        }
    }
    return 0;
}