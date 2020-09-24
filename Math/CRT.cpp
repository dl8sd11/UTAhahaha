ll mod;
ll mul(ll v1,ll v2,ll md=mod) {
    return v1 * v2 % md;
}

void normal(ll &v1) {
    v1 %= mod;
    if (v1 < 0) {
        v1 += mod;
    }
}

ll extGCD(ll n1,ll n2,ll &x1,ll &x2) {
    if (n1 == 0) {
        x2 = 1;
        x1 = 0;
        return n2;
    }
    ll cx1,cx2;
    ll ret = extGCD(n2%n1,n1,cx1,cx2);
    x2 = cx1;
    x1 = cx2 - n2/n1*cx1;
    return ret;
}

void crt (ll a, ll n, ll b, ll m) {
    ll r1,r2;
    ll gcd = extGCD(n,m,r1,r2);
    if ((b-a) % gcd != 0) {
        cout << "no solution" << endl;
        return;
    }
    mod = n * m / gcd;

    ll ans = mul(mul(r1,(b-a)/gcd,m/gcd),n) + a;
    normal(ans);
    cout << ans << " " << mod <<  endl;
}