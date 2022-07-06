#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

map<char, int> c_f;//用于存放输入字符与频率
map<char, string> stu_c_f;//用于存放学生的字符与代码
map<char, string> Huffman;//用于存放每个字符的霍夫曼编码
int N;//字符的个数
typedef struct CTree TreeNode;
typedef struct CTree* Tree;

struct CTree//前缀码树
{
    char Element;
    Tree Left;
    Tree Right;
} ;

typedef struct HuffTree HuffTreeNode;
typedef struct HuffTree *HTree;
struct HuffTree//霍夫曼树
{
    int freq; // 出现频率，即权重
    char key;
    HTree left;
    HTree right;
}  ;


struct n_Heap//堆
{
    HTree heap[300];
    int size;
};
struct n_Heap heap;
//以下函数是堆操作函数，不详细介绍
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
//计算霍夫曼编码
void count_code(HTree proot,string code)
{
    if(proot == nullptr)
        return;
    if(proot->left)
        code +='0';
    count_code(proot->left,code);
    if(!proot->left && !proot->right)
    {
        Huffman[proot->key]=code;//储存霍夫曼编码
    }
    code.pop_back();
    if(proot->right)
    {
        code +='1';
    }
    count_code(proot->right,code);
}
int min_num = 0;
void is_true()//判断同学编码是否正确
{
    int num=0;
    map<char, int>::iterator it;
    for (it = c_f.begin(); it != c_f.end(); it++)//计算同学编码的加权长
    {
        num += stu_c_f[it->first].size() * c_f[it->first];
    }
    if(num!=min_num)//如果该编码的加权长不符合最佳加权长，就return
    {
        cout<<"No"<<endl;
        return;
    }
    Tree proot = (Tree)malloc(sizeof(TreeNode));
    proot->Left=nullptr; 
    proot->Right=nullptr;
    proot->Element='\0';
    for (it = c_f.begin(); it != c_f.end(); it++)
    {
        Tree p=proot;
        
        for(int i=0;i<stu_c_f[it->first].size();i++)
        {
            if(stu_c_f[it->first][i]=='0'){
                if(p->Left==nullptr)
                {
                    if(p->Element!='\0')//如果该字符要放在其他字符的后续节点，则return
                    {
                        cout << "No" << endl;
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
                    if (p->Element != '\0') //如果该字符要放在其他字符的后续节点，则return
                    {
                        cout << "No" << endl;
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
        if((p->Left!=nullptr || p->Right !=nullptr)||p->Element!='\0')//如果该字符放在非叶节点处或其他字符的位置，则return
        {
            cout<<"No"<<endl;
            return;
        }
        p->Element = it->first;
    }
    cout<<"Yes"<<endl;//前面的条件都符合，则该同学编码正确
}
int main()
{
    cin>>N;
    for(int i=0;i<N;i++)//读入字符与频率
    {
        char c;
        cin>>c;
        int f;
        cin>>f;
        c_f[c]=f;
        HTree pt = (HTree)malloc(sizeof(HuffTreeNode));
        pt->freq=f;
        pt->key=c;
        pt->left=nullptr;
        pt->right=nullptr;
        heap.heap[i+1]=pt;
    }
    heap.size=N;
    for (int i = heap.size / 2; i > 0; i--)//构建堆
    {
        p_down(i);
    }
    while (heap.size>1)
    {
        HTree proot = (HTree)malloc(sizeof(HuffTreeNode));
        HTree pl,pr;
        //每次取两个频率最小的树
        pl=heap.heap[1];
        swap(1,heap.size--);
        p_down(1);
        pr = heap.heap[1];
        swap(1, heap.size--);
        
        //合并树，并将频率相加，压入heap中
        p_down(1);
        proot->freq=pl->freq+pr->freq;
        proot->left=pl;
        proot->right=pr;
        heap.heap[++heap.size]=proot;
        p_up(heap.size);
    }
    
    string code;
    count_code(heap.heap[1],code);//霍夫曼编码

    map<char,int>::iterator it;
    min_num=0;
    for(it=c_f.begin();it!=c_f.end();it++)//计算最优加权长
    {   
        min_num+=Huffman[it->first].size()*c_f[it->first];
    }
    // cout<<min_num<<endl;
    int num_s;
    cin>>num_s;
    Tree T=(Tree)malloc(sizeof(TreeNode));
    for(int i=0;i<num_s;i++)//读入同学提交的编码
    {
        for(int j=0;j<N;j++)
        {
            char c;
            cin>>c;
            string code;
            cin>>code;
            stu_c_f[c]=code;
        }
        is_true();//进行判断
    }
    // cout<<"1"<<endl;
}