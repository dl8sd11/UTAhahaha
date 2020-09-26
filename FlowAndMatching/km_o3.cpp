// from http://sunmoon-template.blogspot.com/2016/05/kuhn-munkres-algorithm.html
#define MAXN 100
#define INF INT_MAX
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int px[MAXN],py[MAXN],match_y[MAXN],par[MAXN];
int n;
void adjust(int y){
	match_y[y]=py[y];
	if(px[match_y[y]]!=-2)
		adjust(px[match_y[y]]);
}
bool dfs(int x){
	for(int y=0;y<n;++y){
		if(py[y]!=-1)continue;
		int t=lx[x]+ly[y]-g[x][y];
		if(t==0){
			py[y]=x;
			if(match_y[y]==-1){
				adjust(y);
				return 1;
			}
			if(px[match_y[y]]!=-1)continue;
			px[match_y[y]]=y;
			if(dfs(match_y[y]))return 1;
		}else if(slack_y[y]>t){ 
			slack_y[y]=t;
			par[y]=x;
		}
	}
	return 0;
}
inline int km(){
	memset(ly,0,sizeof(int)*n);
	memset(match_y,-1,sizeof(int)*n);
	for(int x=0;x<n;++x){
		lx[x]=-INF;
		for(int y=0;y<n;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<n;++x){
		for(int y=0;y<n;++y)slack_y[y]=INF;
		memset(px,-1,sizeof(int)*n);
		memset(py,-1,sizeof(int)*n);
		px[x]=-2;
		if(dfs(x))continue;
		bool flag=1;
		while(flag){
			int cut=INF;
			for(int y=0;y<n;++y)
				if(py[y]==-1&&cut>slack_y[y])cut=slack_y[y];
			for(int j=0;j<n;++j){
				if(px[j]!=-1)lx[j]-=cut;
				if(py[j]!=-1)ly[j]+=cut;
				else slack_y[j]-=cut;
			}
			for(int y=0;y<n;++y){
				if(py[y]==-1&&slack_y[y]==0){
					py[y]=par[y];
					if(match_y[y]==-1){
						adjust(y);
						flag=0;
						break;
					}
					px[match_y[y]]=y;
					if(dfs(match_y[y])){
						flag=0;
						break;
					}
				}
			}
		}
	}
	int ans=0;
	for(int y=0;y<n;++y)if(g[match_y[y]][y]!=-INF)ans+=g[match_y[y]][y];
	return ans;
}
