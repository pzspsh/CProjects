/*
@File   : test4.c
@Author : pan
@Time   : 2023-06-11 11:36:46
*/

#include <stdio.h>
/*
类型转换
    类型转换是将一个数据类型的值转换为另一种数据类型的值。
C 语言中有两种类型转换：
隐式类型转换：
    隐式类型转换是在表达式中自动发生的，无需进行任何明确的指令或函数调用。它通常是将一种较小的类型自动转换为较大的类型，例如，将int类型转换为long类型或float类型转换为double类型。隐式类型转换也可能会导致数据精度丢失或数据截断。
显式类型转换：
    显式类型转换需要使用强制类型转换运算符（type casting operator），它可以将一个数据类型的值强制转换为另一种数据类型的值。强制类型转换可以使程序员在必要时对数据类型进行更精确的控制，但也可能会导致数据丢失或截断。
*/
int main()
{
    int i = 10;
    float f = 3.14;
    double d = i + f; // 隐式将int类型转换为double类型
    double d1 = 3.14159;
    int i1 = (int)d1; // 显式将double类型转换为int类型
    printf(i);
    printf("%f", f);
    printf("%d", d);
    printf("%d", d1);
    printf(i1);
}
