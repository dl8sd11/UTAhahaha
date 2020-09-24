struct SuffixArray {
    string s;
    ll n;
    vector<ll> sa,rk,hei,t;
    SuffixArray(string si): s(si),n(SZ(s)),sa(n),rk(n),hei(n),t(n) {
        REP (i,n) {
            rk[sa[i]=i] = s[i];
        }
        t[n-1] = -1;
        for (ll h=1;t[n-1] != n-1; h <<= 1) {
            auto cmp = [&](ll i,ll j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    return (i+h < n && j+h < n) ? (rk[i+h] < rk[j+h]) : (i > j);
                } 
            };
            sort(ALL(sa),cmp);
            t[0] = 0;
            REP1 (i,n-1) {
                t[i] = t[i-1] + cmp(sa[i-1],sa[i]);
            }
            REP (i,n) {
                rk[sa[i]] = t[i];
            }
        }
        ll con = 0;
        REP (i,n) {
            if (rk[i] == 0) {
                hei[0] = con = 0;
            } else {
                if (con) {
                    con--;
                }
                while (s[i+con] == s[sa[rk[i]-1]+con]) {
                    con++;
                }
                hei[rk[i]] = con;
            }
        }
    }
    ll operator [] (ll idx) {
        return sa[idx];
    }
};