#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "pj2_fheap.h"
#include "pj2_nheap.h"

#define LOG2(x) ((log((double)(x))) / (log(2.0)))


 void remove_node(FibNode *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

 void add_node(FibNode *node, FibNode *root)
{
    node->left = root->left;
    root->left->right = node;
    node->right = root;
    root->left = node;
}

FibHeap *make_heap()
{
    FibHeap *heap;

    heap = (FibHeap *)malloc(sizeof(FibHeap));
    if (heap == NULL)
    {
        printf("Error: make FibHeap failed\n");
        return NULL;
    }

    heap->keyNum = 0;
    heap->maxDegree = 0;
    heap->min = NULL;
    heap->cons = NULL;

    return heap;
}

 FibNode *make_node(Type key)
{
    FibNode *node;

    node = (FibNode *)malloc(sizeof(FibNode));
    if (node == NULL)
    {
        printf("Error: make Node failed\n");
        return NULL;
    }
    node->key = key;
    node->degree = 0;
    node->left = node;
    node->right = node;
    node->parent = NULL;
    node->child = NULL;

    return node;
}


 void insert_node(FibHeap *heap, FibNode *node)
{
    if (heap->keyNum == 0)
        heap->min = node;
    else
    {
        add_node(node, heap->min);
        if (T[node->key].Dist < T[heap->min->key].Dist)
            heap->min = node;
    }
    heap->keyNum++;
}


void insert_key(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap == NULL)
        return;

    node = make_node(key);
    if (node == NULL)
        return;

    insert_node(heap, node);
}


 FibNode *remove_min(FibHeap *heap)
{
    FibNode *min = heap->min;

    if (heap->min == min->right)
        heap->min = NULL;
    else
    {
        remove_node(min);
        heap->min = min->right;
    }
    min->left = min->right = min;

    return min;
}

 void link(FibHeap *heap, FibNode *node, FibNode *root)
{
    remove_node(node);
    if (root->child == NULL)
        root->child = node;
    else
        add_node(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = 0;
}

 void make_cons(FibHeap *heap)
{
    int old = heap->maxDegree;

    
    heap->maxDegree = LOG2(heap->keyNum) + 1;

    if (old >= heap->maxDegree)
        return;

    heap->cons = (FibNode **)realloc(heap->cons,
                                     sizeof(FibHeap *) * (heap->maxDegree + 1));
}


 void consolidate(FibHeap *heap)
{
    int i, d, D;
    FibNode *x, *y, *tmp;

    make_cons(heap); 
    D = heap->maxDegree + 1;

    for (i = 0; i < D; i++)
        heap->cons[i] = NULL;

    while (heap->min != NULL)
    {
        x = remove_min(heap); 
        d = x->degree;                
        while (heap->cons[d] != NULL)
        {
            y = heap->cons[d];   
            if (T[x->key].Dist > T[y->key].Dist) 
            {
                tmp = x;
                x = y;
                y = tmp;
            }
            link(heap, y, x); 
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;

    for (i = 0; i < D; i++)
    {
        if (heap->cons[i] != NULL)
        {
            if (heap->min == NULL)
                heap->min = heap->cons[i];
            else
            {
                add_node(heap->cons[i], heap->min);
                if (T[(heap->cons[i])->key].Dist < T[heap->min->key].Dist)
                    heap->min = heap->cons[i];
            }
        }
    }
}

FibNode *min_off(FibHeap *heap)
{
    if (heap == NULL || heap->min == NULL)
        return NULL;

    FibNode *child = NULL;
    FibNode *min = heap->min;
    while (min->child != NULL)
    {
        child = min->child;
        remove_node(child);
        if (child->right == child)
            min->child = NULL;
        else
            min->child = child->right;

        add_node(child, heap->min);
        child->parent = NULL;
    }

    remove_node(min);
    if (min->right == min)
        heap->min = NULL;
    else
    {
        heap->min = min->right;
        consolidate(heap);
    }
    heap->keyNum--;

    return min;
}

void min_free(FibHeap *heap)
{
    FibNode *node;

    if (heap == NULL || heap->min == NULL)
        return;

    node = min_off(heap);
    if (node != NULL)
        free(node);
}

 void renew_degree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent->parent != NULL)
        renew_degree(parent->parent, degree);
}


 void cut_heap(FibHeap *heap, FibNode *node, FibNode *parent)
{
    remove_node(node);
    renew_degree(parent, node->degree);
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = 0;
    add_node(node, heap->min);
}


 void cascading(FibHeap *heap, FibNode *node)
{
    FibNode *parent = node->parent;
    if (parent != NULL)
        return;

    if (node->marked == 0)
        node->marked = 1;
    else
    {
        cut_heap(heap, node, parent);
        cascading(heap, parent);
    }
}


 void decrease_heap(FibHeap *heap, FibNode *node, Type key)
{
    FibNode *parent;

    if (heap == NULL || heap->min == NULL || node == NULL)
        return;

    if (T[key].Dist >= T[node->key].Dist)
    {
        return;
    }

    node->key = key;
    parent = node->parent;
    if (parent != NULL && T[node->key].Dist < T[parent->key].Dist)
    {
        cut_heap(heap, node, parent);
        cascading(heap, parent);
    }
    if (T[node->key].Dist < T[heap->min->key].Dist)
        heap->min = node;
}


 FibNode *search_node(FibNode *root, Type key)
{
    FibNode *t = root; // 临时节点
    FibNode *p = NULL; // 要查找的节点

    if (root == NULL)
        return root;

    do
    {
        if (t->key == key)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search_node(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}


 FibNode *search_heap(FibHeap *heap, Type key)
{
    if (heap == NULL || heap->min == NULL)
        return NULL;

    return search_node(heap->min, key);
}


void delete_key(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap == NULL || heap->min == NULL)
        return;

    node = search_heap(heap, key);
    if (node == NULL)
        return;

    Type min = heap->min->key;
    decrease_heap(heap, node, min - 1);
    min_off(heap);
    free(node);
}

void f_Dijkstra(Table T)
{
    T[Start].Dist = 0;
    FibHeap* heap=make_heap();
    for(int i=1;i<=m;i++)
    {
        insert_key(heap,i);
    }
    Vertex V, W;
    for(int i=1;i<=m;i++)
    {
        V=heap->min->key;
        min_off(heap);
        T[V].Known = 1;
        List p = T[V].Header->NextNode;
        while (p != NULL)
        {
            if (!T[p->n].Known)
            {
                if (T[V].Dist + p->dist < T[p->n].Dist)
                {
                    T[p->n].Dist = T[V].Dist + p->dist;
                    T[p->n].Path = V;
                    delete_key(heap,V);
                    insert_key(heap,V);
                }
            }
            p = p->NextNode;
        }
    }
}