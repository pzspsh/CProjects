/*
@File   : test4.c
@Author : pan
@Time   : 2023-12-23 15:25:59
*/
#include <stdio.h>
#include <windows.h>

void demo(int &s)
{
    s = +1;
    return;
}

int main()
{
    SetConsoleOutputCP(65001);
    int t;
    demo(t);
    printf("输出:%d\n", t);
    return 0;
}