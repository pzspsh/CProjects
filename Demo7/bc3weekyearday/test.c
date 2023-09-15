/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 11:15:03
*/
#include <windows.h>
#include <stdio.h>
const char *WeekYearday(int years, int months, int days)
{
    if (months > 12 || days > 31)
    {
        return "你输入的日期格式错误！！！";
    }
    int WeekDay = -1;
    if (1 == months || 2 == months)
    {
        months += 12;
        years--;
    }
    WeekDay = (days + 1 + 2 * months + 3 * (months + 1) / 5 + years + years / 4 - years / 100 + years / 400) % 7;
    switch (WeekDay)
    {
    case 0:
        return "星期天[Sunday]";
        break;
    case 1:
        return "星期一[Monday]";
        break;
    case 2:
        return "星期二[Tuesday]";
        break;
    case 3:
        return "星期三[Wednesday]";
        break;
    case 4:
        return "星期四[Thursday]";
        break;
    case 5:
        return "星期五[Friday]";
        break;
    case 6:
        return "星期六[Saturday]";
        break;
    default:
        return NULL;
        break;
    }
    return NULL;
}
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int year, month, day;
    char ch = '1';
    while (ch != '\033')
    {
        printf("请输入日期,格式为：2023-01-01\n");
        scanf("%d-%d-%d", &year, &month, &day);
        const char *p = WeekYearday(year, month, day);
        printf("今天是:%s\n", p);
        ch = getchar();
        printf("\n");
        break;
    }
    return 0;
}