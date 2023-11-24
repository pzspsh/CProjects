/*
@File   : test.c
@Author : pan
@Time   : 2023-11-23 19:16:51
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*同构数*/
void tg_num(int a, int b);
int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    tg_num(a, b);
}

void tg_num(int a, int b)
{
    int ch, i, j_num, j, ch_num, flag, pd;
    pd = 1;
    for (i = a; i < b + 1; i++)
    {
        j = i;
        ch = i * i;
        flag = 1;
        while (j != 0)
        {
            j_num = j % 10;
            ch_num = ch % 10;
            if (j_num != ch_num)
            {
                flag = 0;
                break;
            }
            j = j / 10;
            ch = ch / 10;
        }
        if (flag == 1 && pd == 1)
        {
            printf("%d", i);
            pd = 0;
        }
        else if (flag == 1)
        {
            printf(" %d", i);
        }
    }
}