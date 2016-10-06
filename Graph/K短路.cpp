#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define MAXN 1011
#define INF 999999999
int n,m,s,t,k,dis[MAXN];
struct node
{
         int v,c;
         node(int v,int c):v(v),c(c){}
         inline bool operator<(const node &b) const//�������ȶ����ȳ�������
         {
                   return c+dis[v]>b.c+dis[b.v];
         }
};
vector<node> map1[MAXN];//����dijkstra�㷨
vector<node> map2[MAXN];//����A_star�㷨
void dijkstra()
{
         int i,find[MAXN],v;
         for(i=1;i<=n;i++)dis[i]=INF;
         memset(find,0,sizeof(find));
         priority_queue<node> heap;
         dis[t]=0;
         heap.push(node(t,0));
         while(!heap.empty())
         {
                   v=heap.top().v;
                   heap.pop();
                   if(find[v])continue;
                   find[v]=1;
                   for(i=0;i<map1[v].size();i++)
                            if(!find[map1[v][i].v] && dis[v]+map1[v][i].c<dis[map1[v][i].v])
                            {
                                     dis[map1[v][i].v]=dis[v]+map1[v][i].c;
                                     heap.push(node(map1[v][i].v,dis[map1[v][i].v]));
                            }
         }
}
int A_star()
{
         int i,cnt[MAXN],v,g;
         if(dis[s]==INF)return -1;
         priority_queue<node> heap;
         memset(cnt,0,sizeof(cnt));
         heap.push(node(s,0));//0��g��x��
         while(!heap.empty())
         {
                   v=heap.top().v;
                   g=heap.top().c;
                   heap.pop();
                   cnt[v]++;
                   if(cnt[t]==k)return g;
                   if(cnt[v]>k)continue;
                   for(i=0;i<map2[v].size();i++)
                            heap.push(node(map2[v][i].v,g+map2[v][i].c));
         }
         return -1;
}
int main()
{
         int i,u,v,c;
         cin>>n>>m;
         for(i=0;i<m;i++)
         {
                   cin>>u>>v>>c;
                   map2[u].push_back(node(v,c));
                   map1[v].push_back(node(u,c));//���򴢴�����ڵ㵽Ŀ��ڵ����̾���
         }
         cin>>s>>t>>k;
         if(s==t)k++;
         dijkstra();
         int ans=A_star();
         cout<<ans<<endl;
         return 0;
}
