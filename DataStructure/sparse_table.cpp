int st[MAXLG][MAXN];
void build(){
  for(int i=1;i<MAXLG;i++){
    for(int j=0;j<MAXN;j++){
      if(j+(1<<(i-1)) >= MAXN)continue;
      st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
  }
}

int query(int l,int r){ // [l,r]
  int E = __lg(r-l);
  return min(st[E][l],st[E][r-(1<<E)+1]);
}