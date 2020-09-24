// Determining solution for bounded flow system without source and sink
int n, m; cin>>n>>m;
vector<int> sumin(n,0), sumout(n,0);
int N = n+5; int SS = N-1, TT = N-2; // New source and new sink
Dinic dd(N,SS,TT); // Need to call Dinic implementation
ll totlow = 0;
REP(cnt, m){
    int a, b, l, u; cin>>a>>b>>l>>u; a--; b--; // l is lower bound, u is upper bound
    sumout[a] += l; sumin[b] += l;
    dd.add(a,b,u-l); totlow+=l;
}
// For bounded flow with source and sink, simply add edge from t to s with infinite capacity and do the same thing
REP(i,n){
    dd.add(SS,i,sumin[i]); dd.add(i,TT,sumout[i]);
}
ll f = dd.mf();
if (f == totlow)
    cout<<"YES\n";
else
    cout<<"NO\n";
