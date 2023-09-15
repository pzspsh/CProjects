/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 14:05:11
*/
// 3.函数编程题
#include <windows.h>
#include <stdio.h>
#include <string.h>
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    const int N = 1000;
    char str[N];
    printf("请求你要提取数据求和的字符串：");
    scanf("%s", str);
    int n = strlen(str);
    int t[N];
    memset(t, -1, sizeof(t));
    int k = 0;
    int flag = -1;
    int temp = 0;
    int i;
    for (i = 0; i <= n; i++)
    {
        if ((str[i] >= '0') && (str[i] <= '9'))
        {
            if (flag == 1)
            {
                temp = temp * 10 + str[i] - '0';
            }
            else
            {
                flag = 1;
                temp = str[i] - '0';
            }
        }
        else
        {
            if (flag == 1)
            {
                t[k] = temp;
                k++;
            }
            flag = 0;
        }
    }
    int sum = 0;
    for (i = 0; i < N; i++)
    {
        if (t[i] == -1)
            break;
        if (i == 0)
        {
            printf("%d", t[i]);
        }
        else
        {
            printf("+%d", t[i]);
        }
        sum += t[i];
    }
    printf("=%d", sum);
}