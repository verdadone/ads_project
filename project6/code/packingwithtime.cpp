#include<iostream>
#include<algorithm>
#include<time.h>
using namespace std;
class rect{
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
void get(int h,int w)
{cout<<"yes";
  height=h;
  width=w;
}
};
bool cmp(rect x,rect y){
	return x.height>y.height;
}
int main()
{
clock_t start, finish;
double  duration;

int givenWidth;
int N;
cin>>N;
cin>>givenWidth;
rect uv[N];
rect strip[100][100];

for(int i=0;i<N;i++)
{int h,w;
  uv[i].no=i;
  cin>>h>>w;
  uv[i].get(h,w);
}
start = clock();
int height=0;
for(int k=0;k<100000000;k++){
  height=0;
sort(uv,uv+N,cmp);
strip[0][0]=uv[0];
int i=0;
int j=0;
int n=1;
  int wsum=0;
while(1)
{
if(n==N)
break;
    wsum+=strip[i][j].width;
if(wsum+uv[n].width>givenWidth)
{
  i++;
  j=0;
  strip[i][j]=uv[n];
}
else
{
j++;
strip[i][j]=uv[n];
}
n++;
}

for(int k=0;k<=i;k++)
{
  height+=strip[k][0].height;
}
}
finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
cout<<height;
}