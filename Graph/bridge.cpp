/*
from: http://sunmoon-template.blogspot.com
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
struct edge{
	int u,v;
	bool is_bridge;
	edge(int u=0,int v=0):u(u),v(v),is_bridge(0){}
};
std::vector<edge> E;
std::vector<int> G[MAXN];// 1-base
int low[MAXN],vis[MAXN],Time;
int bcc_id[MAXN],bridge_cnt,bcc_cnt;// 1-base
int st[MAXN],top;// for bcc 
inline void add_edge(int u,int v){
	G[u].push_back(E.size());
	E.push_back(edge(u,v));
	G[v].push_back(E.size());
	E.push_back(edge(v,u));
}
void dfs(int u,int re=-1){// re is last edge
	int v;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(size_t i=0;i<G[u].size();++i){
		int e=G[u][i];v=E[e].v;
		if(!vis[v]){
			dfs(v,e^1);//e^1 reverse
			low[u]=std::min(low[u],low[v]);
			if(vis[u]<low[v]){
				E[e].is_bridge=E[e^1].is_bridge=1;
				++bridge_cnt;
			}
		}else if(vis[v]<vis[u]&&e!=re)
			low[u]=std::min(low[u],vis[v]);
	}
	if(vis[u]==low[u]){// build bcc
		++bcc_cnt;// 1-base
		do bcc_id[v=st[--top]]=bcc_cnt;
		while(v!=u);
	}
}
inline void bcc_init(int n){
	Time=bcc_cnt=bridge_cnt=top=0;
	E.clear();
	for(int i=1;i<=n;++i){
		G[i].clear();
		vis[i]=0;
		bcc_id[i]=0;
	}
}

int main () {
    int n, m;
    cin >> n >> m;
    bcc_init(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    dfs(1);
    for (int i=1; i<=n; i++) {
        cout << bcc_id[i] << " \n"[i==n];
    }
}