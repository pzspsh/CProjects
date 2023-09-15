/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 13:36:44
*/
// 2.数组、字符串、结构体、指针编程题
#include <windows.h>
#include <stdio.h>
#define N 100
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int a[N][N];
    int i = 0, j;
    int m, n, sum, max;
    char ch;
    int row = 0;
    int column = 0;
    do
    {
        j = 0;
        do
        {
            scanf("%d", &a[i][j++]);
            ch = getchar();
        } while (ch != ';' && ch != '\n');
        i++;
    } while (ch != '\n');
    m = i;
    n = j;

    max = a[0][0] + a[1][0] + a[0][1] + a[1][1];
    row = 0;
    column = 0;
    for (i = 0, j = 0; i < m - 1; j++)
    {
        sum = a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1];
        if (sum > max)
        {
            row = i;
            column = j;
            max = sum;
        }
        if (j + 1 == n - 1)
        {
            j = 0;
            i++;
        }
    }
    printf("%d %d\n", a[row][column], a[row][column + 1]);
    printf("%d %d\n", a[row + 1][column], a[row + 1][column + 1]);
    return 0;
}
// int main()
// {
//     SetConsoleOutputCP(65001); // 解决乱码问题
//     int a[3][3];
//     int i, j;
//     printf("请输入%d个数:\n", 3 * 3);
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             scanf_s("%d", &a[i][j]);
//         }
//     }
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             printf("%5d", a[i][j]);
//         }
//         printf("\n");
//     }
//     SUM(a);
//     MAXMIN(a);
// }

// int SUM(int a[3][3])
// {
//     int i, j;
//     int sum1 = 0, sum2 = 0;
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             sum1 = a[i][j] + sum1;
//         }
//         printf("第%d行元素之和为%d\n", i, sum1);
//         sum1 = 0;
//     }
//     for (j = 0; j < 3; j++)
//     {
//         for (i = 0; i < 3; i++)
//         {
//             sum1 = a[i][j] + sum1;
//         }
//         printf("第%d列元素之和为%d\n", j, sum1);
//         sum1 = 0;
//     }
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             if (i == j)
//             {
//                 sum1 = a[i][j] + sum1;
//             }
//         }
//     }
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             if (i + j == 2)
//             {
//                 sum2 = a[i][j] + sum2;
//             }
//         }
//     }
//     printf("两条对角线的元素之和分别为%d、%d。\n", sum1, sum2);
//     return 0;
// }

// int MAXMIN(int a[3][3])
// {
//     int m, n, x, y;
//     int max, min;
//     int i, j;
//     max = a[0][0];
//     min = a[2][2];
//     for (i = 0; i < 3; i++)
//     {
//         for (j = 0; j < 3; j++)
//         {
//             if (a[i][j] > max)
//             {
//                 max = a[i][j];
//                 m = i;
//                 n = j;
//             }
//             if (a[i][j] < min)
//             {
//                 min = a[i][j];
//                 x = i;
//                 y = j;
//             }
//         }
//     }
//     printf("最大元素值是%d，位于第%d行第%d列\n", max, m, n);
//     printf("最小元素值是%d，位于第%d行第%d列\n", min, x, y);
//     return 0;
// }