/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 12:15:59
*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int check(int n)
{
    int i;
    if (n == 1)
    {
        return 0;
    }
    for (i = 2; i < n; i++)
    {
        if (n % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
} // 该函数判断一个数是否为质数

void check1(int n)
{
    int i, j, k;
    for (i = 3; i < n - 5; i++)
    {
        for (j = i; j < n - 5; j++)
        {
            for (k = j; k < n - 5; k++)
            {
                if ((i + k + j == n) && check(i) && check(j) && check(k)) // i,j,k的和为 n 同时满足 i,j,k
                {
                    printf("%2d+%2d+%2d=%2d\n", i, j, k, n);
                    break; // 编译输出 并且break终止该循环；
                }
            }
        }
    }
} // 该函数验证一个数为三个质数之和

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int n;
    for (n = 7; n < 100; n = n + 2)
    {
        check1(n); // 先将 7~100 的哥德巴赫猜想 编译出来；
    }
    puts("请输入奇数"); // 再输入一个奇数 对其进行哥德巴赫猜想的验证；
    scanf("%d", &n);    // 键盘输入一个数
    if (n % 2 == 0)
    {
        // 若为偶数
        printf("enter data error");
    }
    else
    {
        check1(n);
    }
    return 0;
}