// #include "project5.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;

#define WPLPERCENT 99
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
// struct n_Heap
// {
//     HTree heap[300];
//     int size;
// };
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
    // Tree(int fr = 0, char k = '\0', Tree *l = nullptr, Tree *r = nullptr) : freq(fr), key(k), left(l), right(r){};
};

struct n_Heap
{
    HTree heap[30000000];
    int size;
};

struct n_Heap heap1;
// map<char, string> Huffman1;
string Huff[20000000];
int WPL = 0;

void swap1(int p1, int p2)
{
    HTree t = heap1.heap[p1];
    heap1.heap[p1] = heap1.heap[p2];
    heap1.heap[p2] = t;
}
int Minf1(int fa, int ls, int rs)
{
    int min = fa;
    int minf = heap1.heap[fa]->freq;
    if (ls <= heap1.size && minf > heap1.heap[ls]->freq)
    {
        minf = heap1.heap[ls]->freq;
        min = ls;
    }
    if (rs <= heap1.size && minf > heap1.heap[rs]->freq)
    {
        minf = heap1.heap[rs]->freq;
        min = rs;
    }
    return min;
}
void p_down1(int v)
{
    int min;
    while (1)
    {
        min = Minf1(v, 2 * v, 2 * v + 1);
        if (min != v)
        {
            swap1(v, min);
            v = min;
        }
        else
            break;
    }
}
void p_up1(int v)
{
    int min;
    while (1)
    {
        int fa = v / 2;
        if (fa == 0)
            break;
        min = Minf1(fa, 2 * fa, 2 * fa + 1);
        if (min != fa)
        {
            swap1(fa, min);
            v = fa;
        }
        else
            break;
    }
}
static string RandomString() {
    string s;
    int bits = rand() % 63 + 1;
    for (int i = 0; i < bits; i++)
        s += to_string(rand() % 2);
    return s;
}

static string RandomString(int bits) {
    string s;
    for (int i = 0; i < bits; i++)
        s += to_string(rand() % 2);
    return s;
}

void count_code(HTree proot, string code)
{
    if (proot == nullptr)
        return;
    if (proot->left)
        code += '0';
    count_code(proot->left, code);
    if (!proot->left && !proot->right)
    {
        WPL+=(proot->freq)*code.size();
    }
    code.pop_back();
    if (proot->right)
    {
        code += '1';
    }
    count_code(proot->right, code);
    delete proot;
}
static void GenerateAnswer(int N, int M, int *frequency, vector<char> v, ofstream &ofs) {
    // PriorityQueue H = Initialize(N, frequency);  // initialize the heap
    // BuildHeap(H);                                // make the heap satisfy heap order
    // HuffmanTree HT = BuildHuffmanTree(H);        // build the weight tree for Huffman Code
    // int WPL = CalWPL(HT, 0);                     // compute the weight path length of the coding
    for (int i = 0; i < N; i++){
        HTree pt = (HTree)malloc(sizeof(HuffTreeNode));
        pt->freq = frequency[i];
        pt->key = v[i];
        pt->left = nullptr;
        pt->right = nullptr;
        heap1.heap[i + 1] = pt;
    }
    heap1.size = N;
    for (int i = heap1.size / 2; i > 0; i--)
    {
        p_down1(i);
    }

    while (heap1.size > 1)
    {
        HTree proot = (HTree)malloc(sizeof(HuffTreeNode));
        HTree pl, pr;
        pl = heap1.heap[1];
        swap1(1, heap1.size--);
        p_down1(1);
        pr = heap1.heap[1];
        swap1(1, heap1.size--);
        p_down1(1);
        proot->freq = pl->freq + pr->freq;
        proot->left = pl;
        proot->right = pr;
        heap1.heap[++heap1.size] = proot;
        p_up1(heap1.size);
    }

    string code;
    count_code(heap1.heap[1], code);

    // for (int i = 0; i < N; i++)
    // {
    //     WPL += Huffman1[v[i]].size() * frequency[i];
    // }

    int *frequencyLeft = new int[N]; // Save how much frequency left
    for (int i = N - 1; i >= 0; i--) {
        if (i == N - 1)
            frequencyLeft[i] = 0;
        else
            frequencyLeft[i] =
             frequency[i + 1] + frequencyLeft[i + 1];
    }

    for (int i = 0; i < M; i++) {
        if (rand() % 100 < WPLPERCENT) { // Try to satisfy the WPL
            int currentWPL = 0;
            int huffmanLength;
            for (int j = 0; j < N; j++) {
                if (j != N - 1)
                    huffmanLength = MIN(rand() % ((WPL - currentWPL - frequencyLeft[j]) / frequency[j]) + 1, 63);
                else 
                    huffmanLength = (WPL - currentWPL) / frequency[j];
                ofs << v[j] << " " <<  RandomString(huffmanLength)  << endl;
                currentWPL += huffmanLength * frequency[j];
            }
        }
        else { // Needn't satisfy the WPL
            for (int j = 0; j < N; j++)
                ofs << v[j] << " " <<  RandomString()  << endl;
        }
    }

    delete [] frequencyLeft;
}
void DataGenerator(int N, int M)
{
    // generate all the character
    vector<char> v;
    // for (char i = '0'; i <= '9'; i++)
    //     v.push_back(i);
    // for (char i = 'a'; i <= 'z'; i++)
    //     v.push_back(i);
    for (int i = 0; i <= N-1; i++)
        v.push_back('A');
    // v.push_back('_');
    std::default_random_engine generator{std::random_device{}()};
    std::shuffle(std::begin(v), std::end(v), generator);

    // choose the random seed and open the file
    ofstream ofs;
    string filename = "testcases_" + to_string(N) + "_" + to_string(M) + ".txt";
    ofs.open(filename, ios::out);

    // generate the character and the frequency
    ofs << N << endl;
    int *frequency = new int[N];
    for (int i = 0; i < N; i++) {
        frequency[i] = rand() % 10 + 1;
        ofs << v[i] << " " << frequency[i] << " ";
    }
    ofs << endl;

    // generate the answer
    ofs << M << endl;
    GenerateAnswer(N, M, frequency, v, ofs);
    
    // close the file
    ofs.close();
    delete [] frequency;
}
int main()
{
    DataGenerator(10,10);
    cout<<"data is generated successfully!"<<endl;
}