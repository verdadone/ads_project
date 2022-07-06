#ifndef _PROJECT5_H_
#define _PROJECT5_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <fstream>

#include <cstdlib>
using namespace std;


typedef struct CTree TreeNode;
typedef struct CTree *Tree;

struct CTree
{
    char Element;
    Tree Left;
    Tree Right;
};

typedef struct HuffTree HuffTreeNode;
typedef struct HuffTree *HTree;
struct HuffTree
{
    int freq; // 出现频率，即权重
    char key;
    HTree left;
    HTree right;
    // string code;
    // Tree(int fr = 0, char k = '\0', Tree *l = nullptr, Tree *r = nullptr) : freq(fr), key(k), left(l), right(r){};
};

struct n_Heap
{
    HTree heap[30000000];
    int size;
};


void swap(int p1, int p2);
int Minf(int fa, int ls, int rs);
void p_down(int v);
void p_up(int v);
void count_code(HTree proot, string code);
void is_true();
void tree();

#endif