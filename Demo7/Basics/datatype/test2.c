/*
@File   : test2.c
@Author : pan
@Time   : 2023-06-11 11:34:35
*/
#include <stdio.h>
#include <float.h>

int main()
{
    printf("float 存储最大字节数 : %lu \n", sizeof(float));
    printf("float 最小值: %E\n", FLT_MIN);
    printf("float 最大值: %E\n", FLT_MAX);
    printf("精度值: %d\n", FLT_DIG);

    return 0;
}