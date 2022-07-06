#include <stdio.h>
#include <math.h>
#define mod 1000000007
//第一个下标代表内部节点个数，第二个下标代表black-height
long long Red[1000][1000];//代表根为红色的红根红黑树
long long Black[1000][1000]; //代表根为黑色的黑根红黑树
int main()
{
    int N;//内部节点的个数
    scanf("%d",&N);
    //定义初始情形
    Black[1][1] = 1; //内部节点为1，black-height为1的黑根红黑树个数为1
    Black[2][1] = 2; //内部节点为2，black-height为1的黑根红黑树个数为2
    Black[3][1] = 1; //内部节点为3，black-height为1的黑根红黑树个数为1
    
    //因为最终的红黑树的根为黑色，所以就不定义红根红黑树的初始情形
    for (int i = 3; i <= N; i++)
    {
        //j为左子树的内部节点个数
        for (int j = 1; j < i - 1; j++)
        {
            //k为black-height
            for (int k = log2(i+1)/2; k <= log2(i+1); k++)
            {
                //对于黑根树来说，它的两棵子的根颜色可以任意，只要保证它的黑色高度是子树的黑色高度加一
                Black[i][k] = (Black[i][k] + (Red[j][k - 1] + Black[j][k - 1]) * (Red[i - j - 1][k - 1] + Black[i - j - 1][k - 1]) ) % mod;//
                //对于红根树来说，它的两棵子树都是黑根树，并且它的黑色高度和子树相同
                Red[i][k] = (Red[i][k]+ Black[j][k] * Black[i - j - 1][k] ) % mod;
            }
        }
    }
    long long sum = 0;
    //统计内部节点为n的子树个数
    for (int i = log2(N + 1)/2; i <= log2(N + 1); i++)//只需要统计可能black-height的子树个数即可
    {
        sum = (sum + Black[N][i]) % mod;
    }
    printf("%lld", sum);
    return 0;

}