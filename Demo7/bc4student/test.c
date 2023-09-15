/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 11:59:32
*/
#include <windows.h>
#include <stdio.h>
#define N 10
struct student
{
    char num[6];
    char name[20];
    int score[3];
} stu[N];
int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    int i, j, imax;
    float sum = 0.0, aver[N], temp, average = 0.0;
    printf("输入学生的学号、姓名和三门课的成绩：\n");
    for (i = 0; i < N; i++)
    {
        scanf("%s%s", &stu[i].num, &stu[i].name);
        for (j = 0; j < 3; j++)
        {
            scanf("%d", &stu[i].score[j]);
            sum += stu[i].score[j];
        }
        aver[i] = sum / 3.0; // 每个学生的平均成绩
        sum = 0;
        average += aver[i];
    }
    average = average / N; // 总平均成绩
    printf("学号   姓名   成绩1    成绩2     成绩3    平均成绩\n");
    for (i = 0; i < N; i++)
    {
        printf("%s%10s", stu[i].num, stu[i].name);
        for (j = 0; j < 3; j++)
            printf("%8d", stu[i].score[j]);
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
    printf("学号   姓名   成绩1    成绩2     成绩3   平均成绩\n");
    printf("%s%10s%5d%5d%5d%7.2f\n", stu[imax].num, stu[imax].name, stu[imax].score[0], stu[imax].score[1], stu[imax].score[2], aver[imax]);
    return 0;
}