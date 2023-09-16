/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 14:05:11
*/
#include <windows.h>
#include <stdio.h>

int sumOfNumbers(const char *s)
{
    int sum = 0;
    int num = 0;

    // 遍历字符串
    for (int i = 0; s[i] != '\0'; i++)
    {
        // 判断当前字符是否为数字
        if (s[i] >= '0' && s[i] <= '9')
        {
            // 将字符转换为数字并累加到当前数值
            num = num * 10 + (s[i] - '0');
        }
        else
        {
            // 遇到非数字字符，将当前数值累加到总和，并重置为0
            sum += num;
            num = 0;
        }
    }

    // 将最后一个数值累加到总和
    sum += num;
    return sum;
}

int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    char s[100];

    printf("请输入一个字符串：");
    fgets(s, sizeof(s), stdin);

    // 调用函数计算和的结果
    int result = sumOfNumbers(s);

    printf("自然数之和为：%d\n", result);

    return 0;
}