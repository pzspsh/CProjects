/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 13:21:12
*/
// 1.基本语法编程题
#include <windows.h>
#include <stdio.h>
int main(void)
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int n, m, i = 1;
    printf("请输入n和m的值：");
    scanf("%d %d", &m, &n);
    for (n = 1; n <= m; n++)
    {
        n = n * i;
    }
    printf("%d", n);
    return 0;
}