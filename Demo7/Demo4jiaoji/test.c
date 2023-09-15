/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 14:37:34
*/
// 4.字符串编程题
#include <stdio.h>
#include <string.h>
void main()
{
    int i, j, n = 0, m, k = 0;
    char str1[100], str2[100], str3[100];
    printf("please input two strings:\n");
    gets(str1);
    gets(str2);
    for (i = 0; i < strlen(str1); i++)
        for (j = 0; j < strlen(str2); j++)
            if (str1[i] == str2[j])
            {
                str3[n++] = str1[i];
                k++;
            }
    for (n = 0; n < k; n++)
        for (m = n + 1; m < k; m++)
            if (str3[n] == str3[m])
                str3[n] = 0;
    for (n = 0; n < k; n++)
        if (str3[n])
            printf(" %c", str3[n]);
}