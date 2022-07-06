#include <stdio.h>
#include <stdlib.h> //  exit() 函数
#include <time.h>
#include <string.h>
#include "pj2_nheap.h"//普通最小堆优化
#include "pj2_fheap.h"//斐波那契最小堆优化
clock_t start, end;//记录时间的开始和结束
int char2int(char *a)//将字符串转换为整数
{
    int i = 0;
    int sum = 0;
    while (*(a + i) != '\0')
    {
        sum = (*(a + i) - '0') + sum * 10;
        i++;
    }
    return sum;
}
int main()
{
    char c[1000];
    Start = 1;
    FILE *fptr;
    if ((fptr = fopen("USA-road-d.NY.gr", "r")) == NULL)//填入要打开的文件地址，如果文件打不开，则报错
    {
        printf("Error! opening file");
        exit(1);
    }
    int cnt = 0;
    while (!feof(fptr))
    {
        fscanf(fptr, "%s", c);//每隔一个空格读入
        if (!strcmp(c,"c"))//“c”代表注释信息，跳过
            continue;
        if (!strcmp(c, "p"))//代表vertex和edge的信息
        {
            fscanf(fptr, "%s", c);
            fscanf(fptr, "%s", c);
            m = char2int(c);//m在pj3_nheap.h里定义，储存vertex数
            fscanf(fptr, "%s", c);
            n = char2int(c); // n在pj3_fheap.h里定义，储存edge数
            Initial(T);
        }
        if (!strcmp(c, "a"))
        {
                //读入有向边
                int v1, v2, dis;
                // scanf("%d %d %d", &v1, &v2, &dis);
                fscanf(fptr, "%s", c);
                v1 = char2int(c);
                fscanf(fptr, "%s", c);
                v2 = char2int(c);
                fscanf(fptr, "%s", c);
                dis = char2int(c);
                List p = T[v1].Header;
                while (p->NextNode != NULL)
                {
                    p = p->NextNode;
                }
                p->NextNode = (List)malloc(sizeof(struct Adjlist));
                p->NextNode->NextNode=NULL;
                p->NextNode->n = v2;
                p->NextNode->dist = dis;
        }
    }
    fclose(fptr);
    start = clock();
    n_Dijkstra(T); //要测试斐波那契堆的时间，则写成"f_Dijkstra(T)";要测试普通最小堆的时间，则写成"n_Dijkstra(T)"
    end = clock();
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC); //输出时间

    return 0;
}