/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 13:36:44
*/
// 2.数组、字符串、结构体、指针编程题
#include <windows.h>
#include <stdio.h>

int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int m, n;
    printf("请输入 m 和 n：");
    scanf("%d %d", &m, &n);

    if (m <= 2 || n <= 2)
    {
        printf("m 和 n 必须大于 2\n");
        return 0;
    }

    double A[m][n];

    printf("请输入 %dX%d 的实数矩阵 A：\n", m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }

    double maxSum = 0, minSum = 0;
    double maxSubMatrix[2][2], minSubMatrix[2][2];

    // 找出元素之和最大的 2x2 子阵
    for (int i = 0; i <= m - 2; i++)
    {
        for (int j = 0; j <= n - 2; j++)
        {
            double sum = A[i][j] + A[i][j + 1] + A[i + 1][j] + A[i + 1][j + 1];
            if (sum > maxSum)
            {
                maxSum = sum;
                maxSubMatrix[0][0] = A[i][j];
                maxSubMatrix[0][1] = A[i][j + 1];
                maxSubMatrix[1][0] = A[i + 1][j];
                maxSubMatrix[1][1] = A[i + 1][j + 1];
            }
        }
    }

    // 找出元素之和最小的 2x2 子阵
    minSum = maxSum; // 初始化为最大和，确保能找到一个更小的值
    for (int i = 0; i <= m - 2; i++)
    {
        for (int j = 0; j <= n - 2; j++)
        {
            double sum = A[i][j] + A[i][j + 1] + A[i + 1][j] + A[i + 1][j + 1];
            if (sum < minSum)
            {
                minSum = sum;
                minSubMatrix[0][0] = A[i][j];
                minSubMatrix[0][1] = A[i][j + 1];
                minSubMatrix[1][0] = A[i + 1][j];
                minSubMatrix[1][1] = A[i + 1][j + 1];
            }
        }
    }

    // 计算差值
    double diff[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            diff[i][j] = maxSubMatrix[i][j] - minSubMatrix[i][j];
        }
    }

    // 输出结果
    printf("元素之和最大的 2X2 子阵：\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%.2f ", maxSubMatrix[i][j]);
        }
        printf("\n");
    }

    printf("元素之和最小的 2X2 子阵：\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%.2f ", minSubMatrix[i][j]);
        }
        printf("\n");
    }

    printf("差值的 2X2 子阵：\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%.2f ", diff[i][j]);
        }
        printf("\n");
    }

    return 0;
}