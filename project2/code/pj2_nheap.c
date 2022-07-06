#include <stdio.h>
#include <stdlib.h>
#include "pj2_nheap.h"
void swap(int p1, int p2)
{
    int t = heap.heap[p1];
    heap.heap[p1] = heap.heap[p2];
    heap.heap[p2] = t;
    t = heap.position[heap.heap[p1]];
    heap.position[heap.heap[p1]] = heap.position[heap.heap[p2]];
    heap.position[heap.heap[p2]] = t;
}
int Mindis(int fa, int ls, int rs)
{
    int min = fa;
    int mind = T[heap.heap[fa]].Dist;
    if (ls <= heap.size && mind > T[heap.heap[ls]].Dist)
    {
        mind = T[heap.heap[ls]].Dist;
        min = ls;
    }
    if (rs <= heap.size && mind > T[heap.heap[rs]].Dist)
    {
        mind = T[heap.heap[rs]].Dist;
        min = rs;
    }
    return min;
}
void p_down(int v)
{
    int min;
    while (1)
    {
        min = Mindis(v, 2 * v, 2 * v + 1);
        if (min != v)
        {
            swap(v, min);
            v = min;
        }
        else
            break;
    }
}
void p_up(int v)
{
    int min;
    while (1)
    {
        int fa = v  / 2;
        if(fa==0)
            break;
        min = Mindis(fa, 2 * fa, 2 * fa + 1);
        if (min != fa)
        {
            swap(fa, min);
            v = fa;
        }
        else
            break;
    }
}

void Initial(Table T)
{
    for(int i=1;i<=n;i++)
    {
        T[i].Header = (List)malloc(sizeof(struct Adjlist));
        T[i].Header->NextNode=NULL;
        T[i].Known = 0;
        T[i].Dist=INF;
        T[i].Path =NotAVetex;
    }
    T[Start].Dist=0;
}
void ReadGraph(Table T)
{
    for(int i=0;i<n;i++)
    {
        int v1,v2,dis;
        scanf("%d %d %d",&v1,&v2,&dis);
        List p= T[v1].Header;
        while(p!=NULL){
            p=p->NextNode;
        }
        p=(List)malloc(sizeof(struct Adjlist));
        p->n=v2;
        p->dist=dis;
    }
}

void n_Dijkstra(Table T)
{
    T[Start].Dist=0;
    initial_nheap();
    Vertex V,W;
    for(int i =heap.size/2;i>0;i--)
    {
        p_down(i);
    }
    // int cnt=0;
    while(1)
    {   
        if(heap.size>0)
            V=heap.heap[1];
        else
            V=NotAVetex;
        if(V==NotAVetex)
            break;
        swap(1,heap.size--);
        p_down(1);
        T[V].Known=1;
        List p=T[V].Header->NextNode;
        while(p!=NULL){
            if(!T[p->n].Known){
                if(T[V].Dist+p->dist<T[p->n].Dist)
                {
                    T[p->n].Dist = T[V].Dist + p->dist;
                    T[p->n].Path = V;
                    p_up(heap.position[p->n]);
                }
            
            }
            p=p->NextNode;
        }
        
    }
}
void PrintPath(Table T,Vertex V)
{
    if(T[V].Path!=NotAVetex)
    {
        PrintPath(T,T[V].Path);
        printf("to");
    }
    printf("%d",V);
}
void initial_nheap()
{
    heap.size = m;
    for (int i = 1; i <= heap.size; i++)
    {
        heap.heap[i] = i;
        heap.position[i]=i;
    }
}
