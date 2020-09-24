const double PI = acos(-1.0);
#define cd complex<double>
 
void FFT(vector<cd> &a, bool rev=0){
    int n = SZ(a); 
    for (int i = 1, j = 0; i<n; i++){
        int bit = n>>1;
        while (j>=bit) j-=bit, bit>>=1; j+=bit;
        if (i<j) swap(a[i], a[j]);
    }
    for (int B = 2; B<=n; B*=2){
        double ang = 2 * PI / B * (rev?-1:1);
        cd w0 (cos(ang), sin(ang));
        for (int i = 0; i<n; i+=B){
            cd w (1,0);
            for (int j = 0; j<B/2; j++){
                cd u = a[i+j], v = w*a[i+j+B/2];
                a[i+j] = u+v, a[i+j+B/2] = u-v;
                w *= w0;
            }
        }
    }
    if (rev) REP(i,n) a[i] /= n;
}
 
vector<ll> mul (vector<ll> a, vector<ll> b){
    int n = 1; while (n < SZ(a) + SZ(b)) n*=2;
    vector<cd> x(n), y(n);
    REP(i, SZ(a)) x[i] = cd(a[i],0); REP(j, SZ(b)) y[j] = cd(b[j],0);
    FFT(x); FFT(y);
    REP(i, n) x[i] *= y[i];
    FFT(x,1);
    vector<ll> re(n);
    REP(i,n) re[i] = min((ll)(round(x[i].real())),1ll);
    while (re.size()>1 && re.back()==0) re.pop_back(); return re;
}
