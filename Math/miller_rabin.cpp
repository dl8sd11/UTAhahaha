ll mul1(ll a, ll b, ll n){ // Better
    __int128 x = a, y = b;
    return (ll)(x*y%n);
}

ll mul2(ll a,ll b,ll n){ // Slightly worse 
    a%=n,b%=n;
    ll y=(ll)((long double)a*b/n+0.5); 
    ll r=(a*b-y*n)%n;
    return r<0?r+n:r;
} 

ll mpow(ll a,ll b,ll mod){//a^b%mod
    ll ans=1;
    for(;b;a=mul1(a,a,mod),b>>=1)
        if(b&1)ans=mul1(ans,a,mod);
    return ans;
}
int sprp[3]={2,7,61};//int
int llsprp[7]={2,325,9375,28178,450775,9780504,1795265022};//unsinged long long 

bool isprime(ll n){
    if(n==2)return 1;
    if(n<2||n%2==0)return 0;
    int t=0;
    ll u=n-1;
    for(;u%2==0;++t)u>>=1;
    for(int i=0;i<5;++i){ // Increase for more accuracy
        ll a=llsprp[i]%n;
        if(a==0||a==1||a==n-1)continue;
        ll x=mpow(a,u,n);
        if(x==1||x==n-1)continue;
        for(int j=1;j<t;++j){
            x=mul1(x,x,n);
            if(x==1)return 0;
            if(x==n-1)break;
        }
        if(x==n-1)continue;
        return 0;
    }
    return 1;
}
