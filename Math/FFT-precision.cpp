#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int(v.size())
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)

const int MAXN = 1<<20;
typedef complex<double> cd;
 
const double pi = acos(-1);
vector<int> bs;
cd omg[MAXN+3];
 
void FFT (vector<cd> &v, int d) {
    for (int i=1,j=SZ(v)>>1; i<SZ(v)-1; i++) {
        if (i < j) {
            swap(v[i], v[j]);
        }
        int k = SZ(v)>>1;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        if (k > j) {
            j += k;
        }
    }
 
    for (int h=2; h<=SZ(v); h<<=1) {
        for (int i=0; i<SZ(v); i+=h) {
            for (int k=i; k<i+h/2; k++) {
                int idx = k-i;
                int r = k+h/2;
                cd x = v[k] - omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[r];
                v[k] = v[k] + omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[r];
                v[r] = x;
            }
        }
    }
 
    if (d < 0) {
        REP (i, SZ(v)) {
            v[i] /= SZ(v);
        }
    }
}
 
void build_omg() {
    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN-1) {
        omg[i] = polar(1.0, i*pi*2/MAXN);
    }
}
 
vector<int> mul (vector<int> &v1, vector<int> &v2) {
    int n = 1;
    while (n < SZ(v1) + SZ(v2)) {
        n <<= 1;
    }
    vector<cd> x(n), y(n);
    REP (i, SZ(v1)) {
        x[i] = v1[i];
    }
    REP (i, SZ(v2)) {
        y[i] = v2[i];
    }
    FFT(x, 1);
    FFT(y, 1);
    REP (i, n) {
        x[i] *= y[i];
    }
    FFT(x, -1);
    vector<int> ret(n);
    REP (i, n) {
        ret[i] = min(1, (int)round(x[i].real()));
    }
    while (SZ(ret)>1 && ret.back() == 0) {
        ret.pop_back();
    }
    return ret; 
}

int main () {
    
}