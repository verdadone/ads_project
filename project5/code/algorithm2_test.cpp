#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include "algorithm2.h"
#include <fstream>
#include <cstdlib>
using namespace std;
map<char, int> c_f;
// map<char, string> stu_c_f;
string s_f[20000000];
int frequency[20000000];

map<char, string> Huffman;
int N;
struct n_Heap heap;
int min_num=0 ;

void swap(int p1, int p2)
{
    HTree t = heap.heap[p1];
    heap.heap[p1] = heap.heap[p2];
    heap.heap[p2] = t;
}
int Minf(int fa, int ls, int rs)
{
    int min = fa;
    int minf = heap.heap[fa]->freq;
    if (ls <= heap.size && minf > heap.heap[ls]->freq)
    {
        minf = heap.heap[ls]->freq;
        min = ls;
    }
    if (rs <= heap.size && minf > heap.heap[rs]->freq)
    {
        minf = heap.heap[rs]->freq;
        min = rs;
    }
    return min;
}
void p_down(int v)
{
    int min;
    while (1)
    {
        min = Minf(v, 2 * v, 2 * v + 1);
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
        int fa = v / 2;
        if (fa == 0)
            break;
        min = Minf(fa, 2 * fa, 2 * fa + 1);
        if (min != fa)
        {
            swap(fa, min);
            v = fa;
        }
        else
            break;
    }
}

void count_code(HTree proot,string code)
{
    if(proot == nullptr)
        return;
    if(proot->left)
        code +='0';
    count_code(proot->left,code);
    if(!proot->left && !proot->right)
    {
        // proot->code=code;
        min_num+=(proot->freq)*(code.size());
    }
    code.pop_back();
    if(proot->right)
    {
        code +='1';
    }
    count_code(proot->right,code);
}
void is_true()
{
    int num=0;
    // map<char, int>::iterator it;
    for (int i=0;i<N;i++)
    {
        num += frequency[i]*s_f[i].size();
    }
    if(num!=min_num)
    {
        // cout<<"No"<<endl;
        return;
    }
    Tree proot = (Tree)malloc(sizeof(TreeNode));
    proot->Left=nullptr;
    proot->Right=nullptr;
    proot->Element='\0';
    for (int i=0;i<N;i++)
    {
        Tree p=proot;
        
        for(int j=0;j<s_f[i].size();j++)
        {
            if(s_f[i][j]=='0'){
                if(p->Left==nullptr)
                {
                    if (p->Element != '\0')
                    {
                        // cout << "No" << endl;
                        return;
                    }
                    p->Left=(Tree)malloc(sizeof(TreeNode));
                    p=p->Left;
                    p->Element='\0';
                    p->Left=nullptr;
                    p->Right=nullptr;
                }
                else p=p->Left;
            }else{
                if (p->Right == nullptr)
                {
                    if (p->Element != '\0')
                    {
                        // cout << "No" << endl;
                        return;
                    }
                    p->Right = (Tree)malloc(sizeof(TreeNode));
                    p = p->Right;
                    p->Element = '\0';
                    p->Left = nullptr;
                    p->Right = nullptr;
                }
                else
                    p = p->Right;
            }
        }
        if((p->Left!=nullptr || p->Right !=nullptr)||p->Element!='\0')
        {
            // cout<<"No"<<endl;
            return;
        }
        p->Element = 'A';
    }
    // cout<<"Yes"<<endl;
}
void tree()
{
    fstream fin("testcases_10_10.txt");
    fin>>N;
    for(int i=0;i<N;i++)
    {
        char c;
        fin>>c;
        int f;
        fin>>f;
        frequency[i]=f;
        // c_f[c]=f;
        HTree pt = (HTree)malloc(sizeof(HuffTreeNode));
        pt->freq=f;
        pt->key=c;
        pt->left=nullptr;
        pt->right=nullptr;
        heap.heap[i+1]=pt;
    }
    heap.size=N;
    for (int i = heap.size / 2; i > 0; i--)
    {
        p_down(i);
    }
    while (heap.size>1)
    {
        HTree proot = (HTree)malloc(sizeof(HuffTreeNode));
        HTree pl,pr;
        pl=heap.heap[1];
        swap(1,heap.size--);
        p_down(1);
        pr = heap.heap[1];
        swap(1, heap.size--);
        p_down(1);
        proot->freq=pl->freq+pr->freq;
        proot->left=pl;
        proot->right=pr;
        heap.heap[++heap.size]=proot;
        p_up(heap.size);
    }
    
    string code;
    count_code(heap.heap[1],code);
    // cout<<min_num<<endl;
    // map<char,int>::iterator it;
    // // min_num = 0;
    //  for (it = c_f.begin(); it != c_f.end(); it++)
    // {   
    //     min_num+=Huffman[it->first].size()*c_f[it->first];
    // }
    // cout<<min_num<<endl;
    int num_s;
    fin>>num_s;
    Tree T=(Tree)malloc(sizeof(TreeNode));
    for(int i=0;i<num_s;i++)
    {
        for(int j=0;j<N;j++)
        {
            char c;
            fin>>c;
            string code;
            fin>>code;
            s_f[j]=code;
        }
        is_true();
    }
    // cout<<"1"<<endl;
    fin.close();
    fin.clear();
}