/*
@File   : test.c
@Author : pan
@Time   : 2023-09-15 14:47:44
*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 快递员工作信息结构体
struct POST
{
    int id;               // 快递员编号
    char name[20];        // 快递员姓名
    int deliveryCount;    // 送快递次数
    int deliveryPerCount; // 每次送的快递件数
    int totalDelivery;    // 送快递总件数
};

// 输入一个快递员的数据
void set(struct POST *post)
{
    printf("请输入快递员编号：");
    scanf("%d", &post->id);
    printf("请输入快递员姓名：");
    scanf("%s", post->name);
    printf("请输入送快递次数：");
    scanf("%d", &post->deliveryCount);
    printf("请输入每次送的快递件数：");
    scanf("%d", &post->deliveryPerCount);

    // 计算送快递总件数
    post->totalDelivery = post->deliveryCount * post->deliveryPerCount;
}

// 输出一个快递员的数据
void print(struct POST *post)
{
    printf("快递员编号：%d\n", post->id);
    printf("快递员姓名：%s\n", post->name);
    printf("送快递次数：%d\n", post->deliveryCount);
    printf("每次送的快递件数：%d\n", post->deliveryPerCount);
    printf("送快递总件数：%d\n", post->totalDelivery);
}

// 比较函数用于qsort排序
int compare(const void *a, const void *b)
{
    struct POST *post1 = (struct POST *)a;
    struct POST *post2 = (struct POST *)b;

    if (post1->totalDelivery == post2->totalDelivery)
    {
        return post1->id - post2->id;
    }
    else
    {
        return post2->totalDelivery - post1->totalDelivery;
    }
}

// 按照送快递总件数由大到小排序
void sort(struct POST *postArray, int size)
{
    qsort(postArray, size, sizeof(struct POST), compare);
}

int main()
{
    SetConsoleOutputCP(65001); // 解决乱码问题
    struct POST postArray[3];

    // 输入3个快递员的数据
    for (int i = 0; i < 3; i++)
    {
        printf("请输入第%d个快递员的数据：\n", i + 1);
        set(&postArray[i]);
    }

    // 按照送快递总件数排序
    sort(postArray, 3);

    // 输出送快递总件数最多的快递员的姓名
    printf("送快递总件数最多的快递员姓名：%s\n", postArray[0].name);

    return 0;
}