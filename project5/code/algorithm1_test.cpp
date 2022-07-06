#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include "algorithm1.h"
using namespace std;
bool cmp(string a, string b)
{
    return a.length() > b.length();
}

priority_queue<int, vector<int>, greater<int>> p;
string codes[20000000];
void print(int N)
{
    sort(codes, codes + N - 1, cmp);
    bool flag = 1;
    for (int x = 0; x < N - 1; x++)
    {
        for (int y = x + 1; y < N; y++)
        {
            if (codes[x].find(codes[y]) == 0)
            {
                flag = 0;
            }
        }
    }
    // if (flag)
    //     // cout << "Yes" << endl;
    // else
        // cout << "No" << endl;
}
int FreSum(int N)
{
    int s = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int a = p.top();
        p.pop();
        int b = p.top();
        p.pop();
        s += a + b;
        p.push(a + b);
    }
    return s;
}
int table[20000000];

void slow()
{
    fstream fin("testcases_10_10.txt");
    int N, M;
    fin >> N;
    char ch;
    int f;
    for (int i = 0; i < N; i++)
    {

        fin >> ch;
        fin >> f;
        table[i] = f;
        p.push(f);
    }
    // for(int i=0;i<p.size();i++)
    // {
    //     cout<<p[i]<<endl;
    // }
    fin >> M;
    int sum = FreSum(N);
    // cout<<sum;
    // int k = 0;
    for (int i = 0; i < M; i++)
    {
        char ch;
        string code;
        int sums = 0;
        for (int j = 0; j < N; j++)
        {
            fin >> ch;
            fin >> code;
            codes[j] = code;
            sums += table[j] * code.length();
        }
        
        if (sums != sum)
        {
            // cout << "No:" <<k<< endl;
            // k++;
        }
        else
        {
            print(N);
        }
    }
}