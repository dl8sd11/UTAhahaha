

void NTT(vector<ll> &a, ll mo, bool rev=0){
    // mo has to be 2^k * c + 1
    int n = SZ(a); 
    while ((n&(-n))!=n) {
        a.pb(0); n++;
    }
    for (int i = 1, j = 0; i<n; i++){
        int bit = n>>1;
        while (j>=bit) j-=bit, bit>>=1; j+=bit;
        if (i<j) swap(a[i], a[j]);
    }
    for (int B = 2; B<=n; B*=2){
        ll w0 = mpow(3,(mo-1)/(B),mo);
        for (int i = 0; i<n; i+=B){
            ll w = 1;
            for (int j = 0; j<B/2; j++){
                ll u = a[i+j], v = w*a[i+j+B/2]%mo;
                a[i+j] = u+v, a[i+j+B/2] = u-v; 
                if (a[i+j]>=mo) a[i+j]-=mo; if (a[i+j+B/2]<0) a[i+j+B/2]+=mo;
                w = w*w0%mod;
            }
        }
    }
    if (rev) {
        reverse(next(a.begin()),a.end());
        ll invn = inv(n,mo);
        REP(i,n) a[i] = a[i]*invn%mod;
    }
}

vector<ll> mul (vector<ll> a, vector<ll> b, ll mo = mod){
    int n = 1; while (n < SZ(a) + SZ(b)) n*=2;
    vector<ll> x(n), y(n);
    REP(i, SZ(a)) x[i] = a[i]; REP(j, SZ(b)) y[j] = b[j];
    NTT(x,mo); NTT(y,mo);
    REP(i, n) x[i] = x[i] * y[i] % mo;
    NTT(x,mo,1);
    while (x.size()>1 && x.back()==0) x.pop_back(); return x;
}
