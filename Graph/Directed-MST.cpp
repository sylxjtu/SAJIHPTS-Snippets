#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <deque>
#include <bitset>
#include <algorithm>
  
using namespace std;
  
const double eps=1e-10;
const double pi=3.1415926535897932384626433832795;
const double eln=2.718281828459045235360287471352;
  
#define LL long long
#define IN freopen("in.txt", "r", stdin)
#define OUT freopen("out.txt", "w", stdout)
#define scan(x) scanf("%d", &x)
#define scan2(x, y) scanf("%d%d", &x, &y)
#define scan3(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define sqr(x) (x) * (x)
#define pr(x) printf("Case %d: ",x)
#define prn(x) printf("Case %d:\n",x)
#define prr(x) printf("Case #%d: ",x)
#define prrn(x) printf("Case #%d:\n",x)
#define lc o << 1
#define rc o << 1 | 1
#define lowbit(x) (x&(-x))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
#define type int//type ��ѡ��int����double

const type inf=2147483640;
const int maxn=1005;

int pre[maxn],id[maxn],vis[maxn];
type in[maxn];

struct edge
{
	int from,to;
	type cost;
	edge(int from=0,int to=0,type cost=0):from(from),to(to),cost(cost){}
}edg[10005];

type ZLEdmonds(int n,int m,int root)//�Ի������뽨ͼʱֱ�Ӻ��ԣ�������룬�����
{
	type tot=0.0;
	//�ж��Ƿ�����
	while(true)
	{
		for(int i=1;i<=n;i++)in[i]=inf;
		for(int i=1;i<=m;i++)
		{
			int u=edg[i].from;
			int v=edg[i].to;
			if(edg[i].cost<in[v] && u!=v){pre[v]=u;in[v]=edg[i].cost;}
		}
		for(int i=1;i<=n;i++)if(i!=root && in[i]==inf)return -1;
		//�һ�
		int cnt=1;
		memset(id,0,sizeof(id));
		memset(vis,0,sizeof(vis));
		in[root]=0;
		for(int i=1;i<=n;i++)//���ÿ����
		{
			tot+=in[i];
			int v=i;
			while(vis[v]!=i && id[v]==0 && v!=root)
			{vis[v]=i;v=pre[v];}
			if(v!=root && id[v]==0)//����
			{
				for(int u=pre[v];u!=v;u=pre[u])id[u]=cnt;
				id[v]=cnt++;
			}
		}
		if(cnt==1)break;
		for(int i=1;i<=n;i++)if(id[i]==0)id[i]=cnt++;
		//������ͼ
		for(int i=1;i<=m;i++)
		{
			int u=edg[i].from;
			int v=edg[i].to;
			edg[i].from=id[u];
			edg[i].to=id[v];
			if(id[u]!=id[v])edg[i].cost-=in[v];
		}
		n=cnt-1;
		root=id[root];
	}
	return tot;
}

int main()
{
	
    return 0;
}

