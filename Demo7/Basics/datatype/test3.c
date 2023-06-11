/*
@File   : test3.c
@Author : pan
@Time   : 2023-06-11 11:35:40
*/
#include <stdio.h>

int main()
{
    float f, x = 3.6, y = 5.2;
    int i = 4, a, b;
    a = x + y;
    b = (int)(x + y);
    f = 10 / i;
    printf("a=%d,b=%d,f=%f,x=%f\n", a, b, f, x);
}