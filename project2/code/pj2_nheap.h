#ifndef _PJ3_NHEAP_H
#define _PJ3_NHEAP_H
#define NotAVetex (0)

typedef int Vertex;
typedef struct Adjlist *List;
struct Adjlist//有向图的邻接表
{
    List NextNode;
    Vertex n;
    int dist;
};
struct TableEntry
{
    List Header;
    int Known;
    int Dist;
    Vertex Path;
};
typedef struct TableEntry Table[30000000];
int m, n;
Vertex Start;
Table T;
struct n_Heap
{
    int heap[70000000];
    int position[70000000];
    int size;
};
#define INF (100000000)
struct n_Heap heap;
void swap(int p1, int p2);//交换堆中的节点
void Initial(Table T);//初始化记录最短路径的表
void ReadGraph(Table T);//读入有向图
void n_Dijkstra(Table T);//使用普通最小堆对Dijkstra算法进行优化
void PrintPath(Table T, Vertex V);
void initial_nheap();//初始化堆
int Mindis(int fa, int ls, int rs);//找到父节点和两个子节点中的最小节点
void p_down(int v);//percolate down
void p_up(int v);  // percolate down
#endif