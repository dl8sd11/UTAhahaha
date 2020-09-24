const int Zero = 0;
inline int opt(const int &a, const int &b){
	return a+b;   
}

int height, width;
int qx, qy, qX, qY;

struct Seg{
	int val;
	Seg *lc, *rc;
};

struct Seg2D{
	Seg *O;
	Seg2D *lc, *rc;
};

Seg* build(int l, int r){
	Seg* ret = new Seg();
	if (l==r) {
		cin>>ret->val;
		return ret;
	}
	int mid  = (l+r)>>1;
	ret->lc = build(l,mid);
	ret->rc = build(mid+1,r);
	ret->val=opt(ret->lc->val, ret->rc->val);
	return ret;
}

Seg* merge(int l, int r, Seg *tl, Seg *tr){
	Seg* ret = new Seg();
	ret->val = opt( tl->val, tr->val);
	
	if (l!=r){
		int mid = (l+r)>>1;
		ret->lc = merge(l,mid,tl->lc,tr->lc);
		ret->rc = merge(mid+1,r,tl->rc,tr->rc);
	}

	return ret;
}


Seg2D* build2D(int l, int r){
	Seg2D* ret = new Seg2D();
	if (l==r){
		ret->O = build(1,width);
		return ret;
	}
	int mid  = (l+r)>>1;
	ret->lc = build2D(l,mid);
	ret->rc = build2D(mid+1,r);
	ret->O = merge(1,width,ret->lc->O,ret->rc->O);
	return ret;	
}

int query(Seg* o, int l, int r, int L, int R){
	if (r<L || R<l) return Zero;
	if (L<=l && r<=R) return o->val;
	int mid = (l+r)>>1;
	int ql = query(o->lc,l,mid,L,R);
	int qr = query(o->rc,mid+1,r,L,R);
	return opt(ql,qr);
}

int query2D(Seg2D* o, int l, int r, int L, int R){
	if (r<L || R<l) return Zero;
	if (L<=l && r<=R) return query(o->O,1,width,qx,qX);
	int mid = (l+r)>>1;
	int ql = query2D(o->lc,l,mid,L,R);
	int qr = query2D(o->rc,mid+1,r,L,R);
	return opt(ql,qr);	
}

int pX, pY, v;

void modify(Seg*o, int l, int r, int p, int v){
	if (l>p||r<p) return;
	if (l==r) {
		o->val=v;
		return;
	}
	int mid = (l+r)>>1;
	modify(o->lc,l,mid,p,v);
	modify(o->rc,mid+1,r,p,v);
	o->val = opt(o->lc->val, o->rc->val);	
}


void modify2D(Seg2D*o, int l, int r, int p){
	if (l>p||r<p) return;
	if (l==r){
		modify(o->O, 1, width, pX,v);
		return;
	}
	int mid = (l+r)>>1;
	modify2D(o->lc,l,mid,p);
	modify2D(o->rc,mid+1,r,p);
	int ql = query(o->lc->O,1,width,pX,pX);
	int qr = query(o->rc->O,1,width,pX,pX);
	modify(o->O,1,width,pX, opt(ql,qr) );
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q; cin>>n>>q;
	width = n;
	height = n;
	Seg2D *S = build2D(1, height);
	while (q--){
		int cmd;
		cin>>cmd;
		if (cmd==1){
			cin>>qy>>qx>>qY>>qX;
			if (qY<qy) swap(qY, qy);
			if (qX<qx) swap(qx, qX);
			cout<<query2D(S, 1, height, qy, qY)<<'\n';
		}else{
			cin>>pY>>pX>>v;
			modify2D(S, 1, height, pY);
		}
		
	}
}
