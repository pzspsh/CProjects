/*
@File   : test.c
@Author : pan
@Time   : 2023-06-08 13:43:27
*/
#include <stdio.h>
int main()
{
    int age;
    printf("Enter your age:");
    scanf("%d", &age);
    if (age >= 18)
    {
        printf("you are eligible for voting");
    }
    else
    {
        printf("you are not eligible for voting");
    }
}