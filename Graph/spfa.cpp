

int spfa(vector<vector<pii> > &g){ // G contains pair<to, cost>
    int n = SZ(g); 
    int s = 0, t = n-1; // Starting node, ending node
    queue<int> q ({s}); 
    vector<int> vis(n,0); // Don't use vector<bool>
    vector<int> dist(n,inf); 
    fill(ALL(dist), inf); dist[s] = 0; 
    while (!q.empty()){ 
        int v = q.front(); q.pop();
        vis[v] = 0;
        for (auto &xx : g[v]) {
            int u = xx.f, w = xx.s;
            if (dist[u] > dist[v] + w){
                dist[u] = dist[v] + w;
                if (!vis[u]){
                    q.push(u); vis[u] = 1;
                }
            }
        }
    }
    return dist[t];
}
