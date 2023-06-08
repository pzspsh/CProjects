/*
@File   : test1.c
@Author : pan
@Time   : 2023-06-08 13:26:04
*/
#include <stdio.h>
int main()
{
    int num;
    printf("Enter your age: ");
    scanf("%d", &num);
    if (num < 18)
    {
        printf("you are not eligible for voting");
    }
    else
    {
        printf("You can vote!!");
    }
    return 0;
}
