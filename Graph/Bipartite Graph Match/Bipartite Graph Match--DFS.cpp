#include<bits/stdc++.h>

using namespace std;

vector<int> g[1005];
int vis[1005];
int vv[1005],res[1005];
int i,j,k,l,m,n,T;

void dfs(int x)//Ⱦɫ�������ͼ
{
	for(unsigned int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(!vis[v])
		{
			vis[v]=-vis[x];dfs(v);
			continue;
		}else if(vis[v]==vis[x])return;
	}
}

bool dfss(int x)
{
	for(unsigned int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(vv[v])continue;
		vv[v]=1;//�����ǰ����ѱ�������(��֦)
		if(res[v]==0||dfss(res[v]))//Ѱ������·
		{
			res[v]=x;//res��ʾ��õ�ƥ��ĵ���
			return true;
		}
	}
	return false;
}

int main()//������Ĭ�϶���ͼ���Ƕ���ͼ�����
{
	memset(vis,0,sizeof(vis));
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)g[i].clear();
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&j,&k);
		g[j].push_back(k);
		g[k].push_back(j);
	}
	for(i=1;i<=n;i++)
		if(!vis[i]){vis[i]=1;dfs(i);}//�Ƚ��кڰ�Ⱦɫ�����ֿ�����ͼ
	memset(res,0,sizeof(res));k=0;
	for(i=1;i<=n;i++)//��������
		if(vis[i]==1)
		{
			memset(vv,0,sizeof(vv));
			if(dfss(i))k++;
		}
	printf("%d",k);//���ƥ����
	return 0;
}
