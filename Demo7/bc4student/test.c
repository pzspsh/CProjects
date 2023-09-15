/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 11:59:32
*/
#include <windows.h>
#include <stdio.h>
#define N 3
struct student
{
    char num[6];
    char name[20];
    char sex[20];
    int english;
    int math;
    int computer;
    // int score[3];
} stu[N];
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int i, j, imax;
    float sum = 0.0, aver[N], temp, average = 0.0;
    printf("输入学生的学号、姓名和三门课的成绩：\n");
    for (i = 0; i < N; i++)
    {
        scanf("%s%s%s", &stu[i].num, &stu[i].name, &stu[i].sex); // &stu[i].english, &stu[i].math, &stu[i].computer
        scanf("%d %d %d", &stu[i].english, &stu[i].math, &stu[i].computer);
        sum += stu[i].english;
        sum += stu[i].math;
        sum += stu[i].computer;
        aver[i] = sum / 3.0; // 每个学生的平均成绩
        sum = 0;
        average += aver[i];
    }
    average = average / N; // 总平均成绩
    printf("学号   姓名  性别   成绩1    成绩2     成绩3    平均成绩\n");
    for (i = 0; i < N; i++)
    {
        printf("%s%5s%5s", stu[i].num, stu[i].name, stu[i].sex);
        printf("%5d%5d%5d", stu[i].english, stu[i].math, stu[i].computer);
        printf("%7.2f\n", aver[i]);
    }
    temp = aver[0];
    for (i = 0; i < N; i++)
        if (aver[i] > temp)
        {
            temp = aver[i];
            imax = i;
        }
    printf("学生的总平均分为：%7.2f\n", average);
    printf("平均分最高的学生的数据为：\n");
    printf("学号   姓名    性别   成绩1    成绩2     成绩3   平均成绩\n");
    printf("%s%10s%10s%5d%5d%5d%7.2f\n", stu[imax].num, stu[imax].name, stu[imax].sex, stu[imax].english, stu[imax].math, stu[imax].computer, aver[imax]);
    return 0;
}