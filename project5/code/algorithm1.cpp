#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
bool cmp(string a, string b) //用来排序的比较函数
{
    return a.length() > b.length();
}
string codes[1000]; //存放编码
void print(int N)   //打印结果
{
    sort(codes, codes + N - 1, cmp); //对编码按长度排序
    bool flag = 1;
    for (int x = 0; x < N - 1; x++) // N^2遍历编码
    {
        for (int y = x + 1; y < N; y++)
        {
            if (codes[x].find(codes[y]) == 0) //如果是前缀码
            {
                flag = 0; //则输出NO
            }
        }
    }
    if (flag)
        cout << "Yes" << endl; //不是前缀码
    else
        cout << "No" << endl; //是
}
priority_queue<int, vector<int>, greater<int>> p; //最小堆
int FreSum(int N)
{
    int s = 0;
    for (int i = 0; i < N - 1; i++) //霍夫曼编码计算长度
    {
        int a = p.top(); //取堆顶元素
        p.pop();
        int b = p.top(); //取堆顶元素
        p.pop();
        s += a + b;    //加和后放回
        p.push(a + b); //加和后放回
    }
    return s; //返回最小加权长度
}
int main()
{

    int N, M;
    cin >> N; //读入数据
    char ch;
    int f;
    int table[1000]; //记录频率
    for (int i = 0; i < N; i++)
    {

        cin >> ch;
        cin >> f;
        table[i] = f; //频率入数组
        p.push(f);    //频率入堆
    }
    cin >> M;
    int sum = FreSum(N); //计算加权和
    // cout<<sum;
    int k = 0;
    for (int i = 0; i < M; i++) //判断学生编码正确性
    {
        char ch;
        string code;
        int sums = 0;
        for (int j = 0; j < N; j++) //遍历每一种方案
        {
            cin >> ch;
            cin >> code;
            codes[j] = code;
            sums += table[j] * code.length(); //计算加权和
        }
        if (sums != sum)          //加权和不是最小值
            cout << "No" << endl; //一定不是最佳编码
        else
            print(N); //进行下一步判断
    }
}