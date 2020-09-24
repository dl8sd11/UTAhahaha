#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, zkw[MAXN*2];

/*
    query: range max
    add: single change value
*/
void build () {
    for (int i=n-1; i>0; i--) {
        zkw[i] = max(zkw[i<<1], zkw[i<<1|1]);
    }
}

void chg (int x, int val) {
    for (zkw[x+=n]=val; x>1; x>>=1) {
        zkw[x>>1] = max(zkw[x], zkw[x^1]);
    }
}

int qry (int l, int r) {
    int ret = -0x3f3f3f3f;
    for (l+=n,r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = max(ret, zkw[l++]);
        }
        if (r&1) {
            ret = max(ret, zkw[--r]);
        }
    }
    return ret;
}

int main () {
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> zkw[i+n];
    }

    build();
    int cmd;
    while (cin >> cmd) {
        int l, r, x, v;
        if (cmd == 1) {
            cin >> l >> r;
            cout << qry(l, r) << endl;
        } else {
            cin >> x >> v;
            chg(x, v);
        }
    }
}