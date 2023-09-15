/*
@File   : fenjie.c
@Author : pan
@Time   : 2023-09-15 10:28:37
*/
#include <windows.h>
#include <stdio.h>
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int n, i;
    printf("请输入整数：");
    scanf("%d", &n);
    printf("%d=", n);
    for (i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            printf("%d", i);
            n /= i;
            if (n != 1)
                printf("*");
        }
    }
    printf("\n");
    return 0;
}