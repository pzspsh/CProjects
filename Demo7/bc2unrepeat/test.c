/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 10:42:00
*/
#include <windows.h>
#include "stdio.h"
int Fact(int n);
int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int i, j, k, n, cnt, cnd;
    printf("请输入整数：");
    scanf("%d", &n);
    cnt = Fact(n);
    cnd = Fact(n - 3);
    printf("组成不重复的总是个数为: %d \n", cnt / cnd);
    for (i = 1; i <= n; i++) // 百位有1,2,3等3种选择
        for (j = 1; j <= n; j++)
            if (j != i) // 十位不等于百位数字时才考察个位,否则另选十位数
                for (k = 1; k <= n; k++)
                    if (k != j && k != i)                    // 个位必须与百位和十位都不同
                        printf("%4d", i * 100 + j * 10 + k); // 输出
    printf("\n");
    return 0;
}

int Fact(int n)
{
    int res = n;
    if (n > 1)
        res = res * Fact(n - 1);
    return res;
}