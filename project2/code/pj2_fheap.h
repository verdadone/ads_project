#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "pj2_fheap.h"
#include "pj2_nheap.h"
#define LOG2(x) ((log((double)(x))) / (log(2.0)))

typedef int Type;

//定义斐波那契堆的节点
typedef struct _FibonacciNode
{
    Type key;                      
    int degree;                    
    struct _FibonacciNode *left;   
    struct _FibonacciNode *right;  
    struct _FibonacciNode *child;  
    struct _FibonacciNode *parent; 
    int marked;                   
} FibonacciNode, FibNode;

//定义斐波那契堆
typedef struct _FibonacciHeap
{
    int keyNum;                   
    int maxDegree;                
    struct _FibonacciNode *min;   
    struct _FibonacciNode **cons; 
} FibonacciHeap, FibHeap;

//移去斐波那契堆的节点
void remove_node(FibNode *node);

//增加节点
void add_node(FibNode *node, FibNode *root);

//创建一个斐波那契堆
FibHeap *make_heap();

//创建一个斐波那契堆的节点
FibNode *make_node(Type key);

//插入一个节点
void insert_node(FibHeap *heap, FibNode *node);

//插入一个值（通过插入节点实现）
void insert_key(FibHeap *heap, Type key);

//将min从根链表中移除
FibNode *remove_min(FibHeap *heap);

//连接节点和根
void link(FibHeap *heap, FibNode *node, FibNode *root);

//创建consolidate所需空间
void make_cons(FibHeap *heap);

//合并斐波那契堆的根链表中左右相同度数的树
void consolidate(FibHeap *heap);

 // 移除最小节点，并返回移除节点后的斐波那契堆
FibNode *min_off(FibHeap *heap);

//释放最小节点空间
void min_free(FibHeap *heap);

//更新度数
void renew_degree(FibNode *parent, int degree);

void cut_heap(FibHeap *heap, FibNode *node, FibNode *parent);
void cascading(FibHeap *heap, FibNode *node);

//将斐波那契堆heap中节点node的值减少为key
void decrease_heap(FibHeap *heap, FibNode *node, Type key);
FibNode *search_node(FibNode *root, Type key);
FibNode *search_heap(FibHeap *heap, Type key);

//删去键值为key的节点
void delete_key(FibHeap *heap, Type key);

//采用斐波那契堆来优化Dijkstra算法
void f_Dijkstra(Table T);
#endif