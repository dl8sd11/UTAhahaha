#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10003;

struct edge{
  int u,v,w,n;
}e[MAXN*2];

int t,n,a,b,c;
int dep[MAXN],sz[MAXN],fat[MAXN],son[MAXN],top[MAXN];
int in[MAXN],cnt,idx,head[MAXN];
int sg[MAXN*2];
char cmd[10];

void add_edge(int u,int v,int w){
  e[cnt].u = u;
  e[cnt].v = v;
  e[cnt].w = w;
  e[cnt].n = head[u];
  head[u] = cnt++;
}

void dfs1 (int nd,int par) {
  dep[nd] = dep[par] + 1;
  sz[nd] = 1;
  fat[nd] = par;
  son[nd] = 0;
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==par) continue;
    dfs1(e[i].v,nd);
    sz[nd] += sz[e[i].v];
    if(sz[e[i].v] > sz[son[nd]]) son[nd] = e[i].v;
  }
}

void dfs2 (int nd,int tp) {
  in[nd] = idx++;
  top[nd] = tp;
  if (son[nd]) dfs2(son[nd],tp);
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==fat[nd] || e[i].v==son[nd]) continue;
    dfs2(e[i].v,e[i].v);
  }
}

int qpath (int x,int y) {
  int ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x,y);
    // ret = max(ret,query(in[top[x]],in[x]+1));
    x = fat[top[x]];
  }
  if(x==y)return ret;
  if (dep[x] < dep[y]) swap(x,y);
//   ret = max(ret,query(in[son[y]],in[x]+1));
  return ret;
}