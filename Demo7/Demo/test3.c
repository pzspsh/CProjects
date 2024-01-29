/*
@File   : test3.c
@Author : pan
@Time   : 2023-12-06 21:27:34
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
int main()
{
    char a[200];
    scanf("%s", a);
    int p = 0;
    for (int i = 0; a[i] == 42; i++)
    {
        p = p + 1;
    }
    int slen = strlen(a);
    for (int j = p; j < slen; j++)
    {
        printf("%c", a[j]);
    }
    for (int k = 0; k < p; k++)
    {
        printf("*");
    }
    return 0;
}