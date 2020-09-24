#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 10000007;

ll inv (ll b, ll mo = mod){
    if (b==1) return b;
    return (mo-mo/b) * inv(mo%b) % mo;
}

void extGCD(ll A,ll B,ll &x,ll &y) { // A p coprime
    if (B == 0) {
        x = 1;
        y = 0;
        assert(A == 1);
        return;
    }
    ll xx,yy;
    extGCD(B,A%B,xx,yy);
    x = yy;
    y = xx - A/B*yy;
    return;
}

ll ext_inv (ll a, ll p) { // a, p co-prime
    ll x, y;
    extGCD(a,p, x, y);
    x %= p;
    if (x < 0) {
        x += p;
    }
    assert(a * x % p);
    return x;
}
int main () {
    ll a, p;
    cin >> a >> p;
    ll ainv = ext_inv(a, p);
    cout << ainv << endl;
}
