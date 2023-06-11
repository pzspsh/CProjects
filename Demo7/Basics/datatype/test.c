/*
@File   : test.c
@Author : pan
@Time   : 2023-06-11 11:25:21
*/
#include <stdio.h>
#include <limits.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);
    printf("int 存储大小：%lu \n", sizeof(int));
    return 0;
}