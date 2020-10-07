// from https://www.lagou.com/lgeduarticle/82099.html
#include<bits/stdc++.h>
#define il inline
#define inc(i,j,k) for(int i=j;i<=k;++i)
#define ra(i,u) for(int i=head[u];i!=-1;i=a[i].nxt)
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int maxm=120010;
const int maxn=2010;
struct node
{
    int to,nxt,flow;
}a[maxm<<1];
int head[maxn],gap[maxn],h[maxn],e[maxn];
bool vis[maxn];
int cnt=-1,n,m,st,ed;
struct cmp {il bool operator () (int x,int y)const{return h[x]<h[y];}};
priority_queue<int,vector<int>,cmp> pq;
queue<int> q;
il void add(int u,int v,int w)
{
    a[++cnt].to=v;
    a[cnt].nxt=head[u];
    a[cnt].flow=w;
    head[u]=cnt;
}
il bool bfs()
{
    memset(h,inf,sizeof(h));
    h[ed]=0;
    q.push(ed);
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        ra(i,t)
        {
            int v=a[i].to;
            if(a[i^1].flow && h[v]>h[t]+1)
            {
                h[v]=h[t]+1;
                q.push(v);
            }
        }
    }
    return h[st]!=inf;
}
il void push(int u)
{
    ra(i,u)
    {
        int v=a[i].to;
        if((a[i].flow) && (h[v]+1==h[u]))
        {
            int df=min(e[u],a[i].flow);
            a[i].flow-=df;
            a[i^1].flow+=df;
            e[u]-=df;
            e[v]+=df;
            if((v!=st)&&(v!=ed)&&(!vis[v]))
            {
                pq.push(v);
                vis[v]=1;
            }
            if(!e[u])break;
        }
    }
}
il void relabel(int u)
{
    h[u]=inf;
    ra(i,u)
    {
        int v=a[i].to;
        if((a[i].flow)&&(h[v]+1<h[u]))h[u]=h[v]+1;
    }
}
inline int hlpp()
{
    if(!bfs())return 0;
    h[st]=n;
    memset(gap,0,sizeof(gap));
    inc(i,1,n) if(h[i]!=inf)gap[h[i]]++;
    ra(i,st)
    {
        int v=a[i].to;
        if(int f=a[i].flow)
        {
            a[i].flow-=f;a[i^1].flow+=f;
            e[st]-=f;e[v]+=f;
            if(v!=st&&v!=ed&&!vis[v])
            {
                pq.push(v);
                vis[v]=1;
            }
        }
    }
    while(!pq.empty())
    {
        int t=pq.top();pq.pop();
        vis[t]=0;push(t);
        if(e[t])
        {
            gap[h[t]]--;
            if(!gap[h[t]])
            {
                inc(v,1,n)
                {
                    if(v!=st&&v!=ed&&h[v]>h[t]&&h[v]<n+1)
                    {
                        h[v]=n+1;
                    }
                }
            }
            relabel(t);gap[h[t]]++;
            pq.push(t);vis[t]=1;
        }
    }
    return e[ed];
}
signed main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&st,&ed);
    inc(i,1,m)
    {
        int x,y;
        ll f;
        scanf("%d%d%lld",&x,&y,&f);
        add(x,y,f);
        add(y,x,0);
    }
    ll maxf=hlpp();
    printf("%lld",maxf);
    return 0;
}
