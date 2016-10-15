﻿/************************************************* 
算法引入： 
最小k度限制生成树,就是指有特殊的某一点的度不能超过k时的最小生成树; 
如果T是G的一个生成树且dT(v0)=k,则称T为G的k度限制生成树; 
G中权值和最小的k度限制生成树称为G的最小k度生成树; 
 
算法思想： 
设特殊的那点为v0,先把v0删除,求出剩下连通图的所有最小生成树; 
假如有m棵最小生成树,那么这些生成树必定要跟v0点相连; 
也就是说这棵生成树的v0点至少是m度的; 
若m>k,条件不成立,无法找到最小k度限制生成树; 
若m<=k,则枚举m到k的所有最小生成树,即一步步将v0点的度加1,直到v0点的度为k为止; 
则v0点度从m到k的(k-m+1)棵最小生成树中最小的那棵即为答案; 
 
算法步骤： 
(1)先求出最小m度限制生成树: 
原图中去掉和V0相连的所有边(可以先存两个图,建议一个邻接矩阵,一个邻接表,用方便枚举边的邻接表来构造新图); 
得到m个连通分量,则这m个连通分量必须通过v0来连接; 
则在图G的所有生成树中dT(v0)>=m; 
则当k<m时,问题无解; 
对每个连通分量求一次最小生成树; 
对于每个连通分量V’,用一条与V0直接连接的最小的边把它与V0点连接起来,使其整体成为一个生成树; 
就得到了一个m度限制生成树,即为最小m度限制生成树; 
 
(2)由最小m度限制生成树得到最小m+1度限制生成树; 
连接和V0相邻的点v,则可以知道一定会有一个环出现(因为原来是一个生成树); 
只要找到这个环上的最大权边(不能与v0点直接相连)并删除,就可以得到一个m+1度限制生成树; 
枚举所有和V0相邻点v,找到替换后,增加权值最小的一次替换(如果找不到这样的边,就说明已经求出); 
就可以求得m+1度限制生成树; 
如果每添加一条边,都需要对环上的边一一枚举,时间复杂度将比较高; 
用动态规划解决; 
设dp(v)为路径v0—v上与v0无关联且权值最大的边; 
定义father(v)为v的父结点,由此可以得到状态转移方程: 
dp(v)=max(dp(father(v)),ω(father(v),v)); 
边界条件为dp[v0]=-∞(因为每次寻找的是最大边,所以-∞不会被考虑),dp[v’]=-∞|(v0,v’)∈E(T); 
 
(3)当dT(v0)=k时停止(即当V0的度为k的时候停止),但不一定k的时候最优; 
 
算法实现： 
并查集+kruskal; 
首先,每个连通分量的的最小生成树可以直接用一个循环,循环着Kruskal求出; 
这里利用了联通分量间的独立性,对每个连通分量分别求最小生成树,和放在一起求,毫不影响; 
而且kruskral算法保证了各连通分量边的有序性; 
找最小边的时候,可以用动态规划,也可以这么做： 
先走一个循环,但我们需要逆过来加边,将与v0关联的所有边从小到达排序; 
然后将各连通分量连接起来,利用并查集可以保证每个连通分量只有一条边与v0相连; 
由于边已经从小到达排序,故与每个连通分量相连的边就是每个连通分量与v0相连中的最小边; 
然后求m+1度的最小生成树时,可以直接用DFS,最小生成树要一直求到k度,然后从中找出一个最优值; 
 
算法测试： 
PKU1639(Picnic Planning); 
 
题目大意: 
给出m条边,每条边有两个端点和一个权值; 
求这个图在满足以下条件的情况下的最小生成树; 
在所有点中,有一个特殊点Park,它在求得的最小生成树中的度必须小于等于某个值; 
**************************************************/  
#include<iostream>  
#include<string>  
#include<cstdio>  
#include<map>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
  
const int INF=99999999;  
const int N=100;  
  
int n,m;//n为边的数量,m表示限度值  
int cnt;//计算出来的结点数  
int set[N];  
bool flag[N][N];  
int G[N][N];  
int ans;  
  
map<string,int> Map;  
  
struct node  
{  
    int x,y,v;  
} a[N*N];  
  
struct edge  
{  
    int x,y,v;  
} dp[N];  
  
int get_num(string s)//返回每个人对应结点  
{  
    if(Map.find(s)==Map.end())//没有搜索到该键值  
    {  
        Map[s]=++cnt;//对应建图  
    }  
    // cout<<"  Map["<<s<<"]=="<<Map[s]<<endl;  
    return Map[s];  
}  
  
bool cmp(node a,node b)  
{  
    return a.v<b.v;  
}  
  
int find_set(int x)  
{  
    if(x!=set[x])  
        set[x]=find_set(set[x]);  
    return set[x];  
}  
  
inline void union_set(int x,int y)  
{  
    set[y]=x;  
}  
  
void kruskal()//求m个连通分量的最小生成树  
{  
    for(int i=1; i<=n; i++)  
    {  
        if(a[i].x==1||a[i].y==1)  
            continue;  
        int x=find_set(a[i].x);  
        int y=find_set(a[i].y);  
        if(x==y)  
            continue;  
        flag[a[i].x][a[i].y]=flag[a[i].y][a[i].x]=true;  
        set[y]=x;  
        ans+=a[i].v;  
    }  
}  
  
void dfs(int x,int fa)  
{  
    for(int i=2; i<=cnt; i++)  
        if(i!=fa&&flag[x][i])  
        {  
            if(dp[i].v==-1)  
            {  
                if(dp[x].v>G[x][i])//dp(v)=max(dp(father(v)),ω(father(v),v));  
                {  
                    dp[i]=dp[x];  
                }  
                else  
                {  
                    dp[i].v=G[x][i];  
                    dp[i].x=x;  
                    dp[i].y=i;  
                }  
            }  
            dfs(i,x);  
        }  
}  
  
void init()  
{  
    ans=0;  
    cnt=1;  
    Map["Park"]=1;  
    memset(flag,0,sizeof(flag));  
    memset(G,-1,sizeof(G));  
    scanf("%d",&n);  
    for(int i=1; i<N; i++)//并查集初始化  
        set[i]=i;  
    string s;  
    for(int i=1; i<=n; i++)  
    {  
        cin>>s;  
        a[i].x=get_num(s);  
        cin>>s;  
        a[i].y=get_num(s);  
        cin>>a[i].v;  
        if(G[a[i].x][a[i].y]==-1)  
            G[a[i].x][a[i].y]=G[a[i].y][a[i].x]=a[i].v;  
        else//有重边  
            G[a[i].x][a[i].y]=G[a[i].y][a[i].x]=min(G[a[i].y][a[i].x],a[i].v);  
    }  
    scanf("%d",&m);//m表示限度值  
}  
  
void solve()  
{  
    int tmp[N],Min[N];  
    for(int i=1; i<=cnt; i++)  
        Min[i]=INF;  
    sort(a+1,a+1+n,cmp);  
    kruskal();  
    for(int i=2; i<=cnt; i++)  
    {  
        if(G[1][i]!=-1)  
        {  
            int t=find_set(i);  
            if(Min[t]>G[1][i])//求每个连通分量中和顶点1连接的最小权边  
            {  
                tmp[t]=i;  
                Min[t]=G[1][i];  
            }  
        }  
    }  
      
    int t=0;//t表示最小限度  
    for(int i=1; i<=cnt; i++)  
        if(Min[i]!=INF)  
        {  
            t++;  
            flag[1][tmp[i]]=flag[tmp[i]][1]=true;  
            ans+=G[1][tmp[i]];  
        }  
          
    for(int i=t+1; i<=m; i++)//枚举t到m的所有最小生成树,即一步步将v1点的度加1,直到v1点的度为m为止;  
    {  
        memset(dp,-1,sizeof(dp));//dp[v]为路径v0—v上与v0无关联且权值最大的边;  
        dp[1].v=-INF;  
        for(int j=2; j<=cnt; j++)  
            if(flag[1][j])  
                dp[j].v=-INF;  
        dfs(1,-1);  
        int tmp,Min=INF;  
        for(int j=2; j<=cnt; j++)  
            if(G[1][j]!=-1)  
            {  
                if(Min>G[1][j]-dp[j].v)  
                {  
                    Min=G[1][j]-dp[j].v;  
                    tmp=j;  
                }  
            }  
        if(Min>=0)//找不到这样的边,就说明已经求出  
            break;  
        flag[1][tmp]=flag[tmp][1]=true;  
        int x=dp[tmp].x;  
        int y=dp[tmp].y;  
        flag[x][y]=false;  
        flag[y][x]=false;  
        ans+=Min;  
    }  
      
    printf("Total miles driven: %d\n",ans);  
}  
  
int main()  
{  
    freopen("C:\\Users\\Administrator\\Desktop\\kd.txt","r",stdin);  
    init();  
    solve();  
    return 0;  
} 