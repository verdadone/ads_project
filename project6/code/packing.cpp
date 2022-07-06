#include<iostream>
#include<algorithm>

using namespace std;
class rect{//新建矩形类
  public:
int no;
int height;
int width;
rect(){};
rect(int h,int w)
{
  height=h;
  width=w;
}
void get(int h,int w)//获取矩形的高度和宽度
{cout<<"yes";
  height=h;
  width=w;
}
};
bool cmp(rect x,rect y){
	return x.height>y.height;//用以比较矩形高度的函数
}
int main()
{
int givenWidth;//给定的条带宽度
int N;//有几个矩形
cin>>N;
cin>>givenWidth;
rect uv[N];//存储矩形的数组
rect strip[100][100];//条带承载矩形位置的数组
for(int i=0;i<N;i++)
{int h,w;
  uv[i].no=i;
  cin>>h>>w;
  uv[i].get(h,w);//自定义矩形数组
}
int height=0;
sort(uv,uv+N,cmp);//按高度从大到小对矩形排序
strip[0][0]=uv[0];//高度最高的矩形放入条带的左下
int i=0;
int j=0;
int n=1;
  int wsum=0;
while(1)
{
if(n==N)
break;
    wsum+=strip[i][j].width;//计算同一层矩形的宽度和
if(wsum+uv[n].width>givenWidth)//如果同一层矩形越界
{
  i++;
  j=0;
  strip[i][j]=uv[n];//新的矩形放入上一层
}
else//否则
{
j++;
strip[i][j]=uv[n];//新的矩形还在本层继续插
}
n++;
}
for(int k=0;k<=i;k++)
{
  height+=strip[k][0].height;//计算高度和
}
cout<<height;
}