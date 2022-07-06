#include<iostream>
#include<vector>
#include <map> 
#define maxn 1005
using namespace std;
int Fruits[maxn][maxn]={0};//建立表示图的二维数组
int n,m;
int price[maxn]={0};//记录价格
vector< vector<int>> setof;//将dfs中每次走的路径存到其中
map<int,vector<int>> paths;//选出所有路径中符合要求的
vector<int> s;//记录dfs每次所走的路径
int temp=0;
bool backtrace(int x)//看新添加的水果能不能和已经添加到路径中的水果一起吃
{if(x==0)return true;
    for(int i=0;i<s.size();i++)
    {
        if(Fruits[s[i]][x]==1)//如果不能
        return false;//则返回不能
    }
    return true;//反之则返回可以
}    
void dfs(int index)//dfs遍历图
{if(s.size()>m)//如果所有点都已经入栈
return;//剪枝退出
    s.push_back(index);//新遇到一个点则将其入栈
    for(int i=index+1;i<maxn;i++)//遍历比当前节点大的有价格的节点
    {//如果此节点与当前节点连接
        if(Fruits[index][i]==0&&price[i]!=0&&backtrace(i)==true)//并且可以和之前已经遍历的水果一同食用
            dfs(i);//将此节点入栈
    }
    setof.push_back(s);//如果没有下一个符合条件节点，则将这条路径入栈
    s.pop_back();//将路径的最末端一位出栈
}
int main()
{
    cin>>n>>m;
    int x,y;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;//读入图中
        Fruits[y][x]=Fruits[x][y]=1;//不能一起吃
    }
    for(int i=0;i<m;i++)
    {         
        cin>>x>>y;
        price[x]=y;//记录价格
    }
    dfs(0);
    int max=0;
    for(int i=0;i<setof.size();i++)
    {
        if(setof[i].size()>max)
        max=setof[i].size();//从所有路径中找出最长路径的值
    }
    cout<<max-1<<endl;
    for(int i=0;i<setof.size();i++)
    {
        if(setof[i].size()==max)//找出最长路径
        {int perprice=0;
            for(int j=0;j<setof[i].size();j++)
            {
                perprice+=price[setof[i][j]];//计算最长路径的价格
            }
            paths.insert(pair<int, vector<int>>(perprice,setof[i]));//将路径及其价格压入map中
        }
    }
    auto itor = paths.begin();//
    printf("%03d",itor->second[1]);
        for(int j=2;j<itor->second.size();j++)
            {
                printf(" %03d",itor->second[j]);//按格式输出
            }
        cout<<endl<<itor->first;//由于map已经自己排序好了，所以可以直接输出
}