/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 14:37:34
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数用于qsort排序
int compare(const void *a, const void *b)
{
    return *(char *)b - *(char *)a;
}

void intersection(char *set1, char *set2, char *result)
{
    int index = 0;

    // 遍历第一个集合中的字符
    for (int i = 0; set1[i] != '\0'; i++)
    {
        // 判断字符是否在第二个集合中出现
        if (strchr(set2, set1[i]) != NULL)
        {
            // 判断字符是否已在结果集合中出现
            if (strchr(result, set1[i]) == NULL)
            {
                result[index++] = set1[i];
            }
        }
    }

    // 添加字符串结束符
    result[index] = '\0';

    // 按字符从大到小排序
    qsort(result, strlen(result), sizeof(char), compare);
}

int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    char set1[20];
    char set2[20];
    char result[20];

    printf("请输入第一个字符集合（用英文逗号分隔）：");
    scanf("%s", set1);

    printf("请输入第二个字符集合（用英文逗号分隔）：");
    scanf("%s", set2);

    // 调用函数计算交集
    intersection(set1, set2, result);

    printf("交集为：%s\n", result);

    return 0;
}