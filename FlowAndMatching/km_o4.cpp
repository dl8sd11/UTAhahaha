const int mxn = 100;

bool vx[mxn], vy[mxn]; // Visited x or y
int my[mxn]; // Match of y
ll slk[mxn], lx[mxn], ly[mxn]; // Slack (on y), value on x, value on y
int g[mxn][mxn]; // Adjacency matrix with weights
int n;
 
bool dfs(int v){
    vx[v] = 1;
    REP(i,n){
        if (vy[i]) continue;
        if (g[v][i] == lx[v] + ly[i]) {
            vy[i] = 1; 
            if (my[i]==-1 || dfs(my[i])){
                my[i] = v; return 1;
            }
        }else{
            MN(slk[i], lx[v] + ly[i] - g[v][i]); 
        }
    }
    return 0;
}
 
ll mxmch(){
    REP(i,n) REP(j,n) MX(lx[i], g[i][j]);
    fill(my, my+n, -1); 
    REP(i,n){
        while (1){
            fill(vx, vx+n, 0); fill(vy, vy+n, 0); fill(slk, slk+n, inf);
            if (dfs(i)) break;
            ll hv = *min_element(slk, slk+n);
            REP(i,n) if (vx[i]) lx[i] -= hv;
            REP(i,n) if (vy[i]) ly[i] += hv;
        }
    }
    ll re= 0;
    REP(i,n) re += g[my[i]][i];
    return re;
}
