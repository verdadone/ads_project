#include<iostream>
#include<string>
#include <cstring>
#include<math.h>
#include<algorithm>
#include <fstream>
#include <cstdlib>
#include<vector>
#include<map>
#include <sstream>
#include<ctime>
using namespace std;
bool cmp (pair<string, vector<int>> a , pair<string, vector<int>> b)//给字典以单词出现次数排序ranking
{
return a.second.size()< b.second.size();//给vector按照size排序
}
clock_t start_t,end_t;//用来计时以比较搜索的threshold
void split(const string& s,vector<string>& sv,const char flag = ' ') {
    sv.clear();
    istringstream iss(s);//用stream读取
    string temp;
    while (getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
    return;
}
map <string,vector<int>> weight;//新建字典，key为词语，value为一个vector，其中存放包含这个词的文档的id
int main()
{vector<int> vec(0);
int N;
cin>>N;//总共读入多少个文档
getchar();
start_t=clock();
for(int id=0;id<N;id++)
{   cout<<id<<endl;
    string F[10000];//用以存储文档的数组
    int i=0;
    char buf[20];
    string idstring=to_string(id);//id转换为可以连接到文件的字符串
    ifstream newfile(idstring+".txt");//读入序号对应的文件
    if (! newfile.is_open())
    {
        cout << "Error opening file"; exit (1);//如果找不到文件则退出
    }
    while (!newfile.eof())
    {
        newfile>>F[i];//将每个单词读入字符串数组中
       i++;
    }
    for(int k=0;k<i;k++)
    {
        F[k].erase(remove(F[k].begin(),F[k].end(),'.'),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),','),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),':'),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),'\''),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),'?'),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),'!'),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),';'),F[k].end());//从单词中清除标点符号
        F[k].erase(remove(F[k].begin(),F[k].end(),'-'),F[k].end());//从单词中清除标点符号
    }
    string Stop[10005];//停止词数组
    int j=0;
 ifstream examplefile("stop.txt");//从文件中读入停止词
    if (! examplefile.is_open())
    {
        cout << "Error opening file"; exit (1);//如果找不到文件则退出
    }
    while (!examplefile.eof())
    {
        examplefile.getline(buf,20);//从文件中读入停止词
        Stop[j]=buf;//从文件中读入停止词
        j++;//从文件中读入停止词
    }
    for(int k=0;k<i;k++)
    {
        for(int p=0;p<sizeof(Stop)/sizeof(Stop[0]);p++)
        {
            if(F[k].compare(Stop[p])==0)//如果读入文档中的单词有停止词
        {
            F[k]="#";//则将其变为#
        }
        }
    }
    int count=0;
    for(int k=0;k<i;k++)
    {
        if(F[k].compare("#")==0)
        {
            count++;//字数统计，有几个非停止词的单词
        }
    }
    cout<<count<<endl;//打印词数
     for(int k=0;k<i;k++)
     {map<string,vector<int>>::iterator it;//新建迭代器遍历字典
     if(F[k].compare("#")==0)//跳过停止词
     continue;
         it=weight.find(F[k]);//查找某词是否在字典中
      if(it==weight.end())//如果不在
      {
          weight.insert( pair<string,vector<int>>(F[k],vec));//新建字典的一行，将这个词加入字典
          weight[F[k]].push_back(id);//在对应的vector中压入这个词对应文档的id
      }
      else//如果在
      {
          //if(weight[F[k]].back()!=id)//如果vector中本身没有这个词所在文档的的id
          weight[F[k]].push_back(id);//在对应的vector中压入这个词对应文档的id
      }
     }
     F->clear();
    }
for(auto i=weight.begin();i!=weight.end();i++)//实现文件阈值
{
    if(i->second.size()>100)//如果某个单词的出现次数过高，高于某个阈值
    {
        weight.erase(i);//将其删除
    }
}
for(auto i=weight.begin();i!=weight.end();i++)
{
    
i->second.erase(unique(i->second.begin(), i->second.end()), i->second.end());//对
}
string search;
getline(cin,search);//输入查询的单词或者phrase
vector<string> phrase;
split(search, phrase, ' ');//将短语中的单词取出存入string的vector中
map<string,vector<int>>::iterator iter;
if(phrase.size()>1)//如果vector中单词多于1个，则进入短语查找模式
{
    vector <int> res=weight[phrase[0]];

for(int i=0;i<phrase.size();i++)//遍历vector
{vector <int> temp;
if(weight.find(phrase[i])==weight.end())
{
cout<<"No Matching"<<endl;//如果有一个单词都没有找到，则退出
return 0;
}
temp=weight[phrase[i]];
set_intersection(temp.begin(),temp.end(),res.begin(),res.end(),back_inserter(res));//求出包含这些单词的篇目序号集合的交集
}
sort(res.begin(), res.end());//排序
    res.erase(unique(res.begin(), res.end()), res.end());//去重
if(res.empty())//如果没有交集
{
    cout<<"No Matching"<<endl;//则输出报错信息
    return 0;//并且退出
}
else//如果有交集，则定位到短语所在的篇目
{    for(int k = 0; k < res.size(); ++k)//输出所在的篇目
        cout << res[k] <<" ";
}
}
else//如果vector中单词不多于1个，则进入单词查找模式
{
if(search.empty())//如过输入的是空条目，则提醒输入空单词
{
cout<<"NULL string"<<endl;//空条目
return 0;//并且退出
}
iter = weight.find(search);//迭代器
if(iter==weight.end())//如果找不到该单词
{
    cout<<"No Matching"<<endl;//输出找不到的信息并退出
    return 0;//结束程序
}
for(int i = 0; i < weight[search].size(); ++i) {//如果找到了则遍历
        cout << weight[search][i] << " ";//并且输出所在的篇目序号
    }
}
end_t=clock();
double endtime=(double)(end_t-start_t)/CLOCKS_PER_SEC;
	cout<<"Total time:"<<endtime*1000<<"ms"<<endl;	//ms为单位

}