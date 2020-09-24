

ll mul1(ll a, ll b, ll n){
    __int128 x = a, y = b;
    return (ll)(x*y%n);
} // A little faster than mul2

ll mul2(ll a,ll b,ll n){
    a%=n,b%=n;
    ll y=(ll)((long double)a*b/n+0.5); 
    ll r=(a*b-y*n)%n;
    return r<0?r+n:r;
}
