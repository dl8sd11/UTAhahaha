#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i, n) for(int i=0; i<n;i++)

const int MAXN = 100005;

int n, m, a[MAXN], len[MAXN*4], dt[MAXN*4], tag[MAXN*4];

void push (int o) {
    if (len[o] > 1 && tag[o] != 0) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        dt[o] += tag[o] * len[o];
        tag[o] = 0;
    }
}

ll sum (int o) {
    return tag[o]*len[o] + dt[o];
}

void pull (int o) {
    dt[o] = sum(o<<1) + sum(o<<1|1);
}

void build (int o=1, int l=0, int r=n) {
    if (l == r - 1) {
        dt[o] = tag[o] = 0;
        len[o] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        len[o] = len[o<<1] + len[o<<1|1];
        pull(o);
    }
}


ll query(int qL, int qR, int o=1, int nL=0, int nR=n) {
    if (qR <= nL || qL >= nR || qL >= qR) {
        return 0;
    } else if (nL >= qL && nR <= qR) {
        return sum(o);
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        return query(qL, qR, o<<1, nL, mid) + query(qL, qR, o<<1|1, mid, nR);
    }
}

void modify(int qL, int qR, int val, int o=1, int nL=0, int nR=n) {
    if (qR <= nL || qL >= nR || qL >= qR) {
        return;
    } else if (nL >= qL && nR <= qR) {
        tag[o] += val;
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        modify(qL, qR, val, o<<1, nL, mid);
        modify(qL, qR, val, o<<1|1, mid, nR);
        pull(o);
    }
}

int main () {
    cin >> n;
    build();
    int cmd;
    while (cin >> cmd) {
        int l, r, v;
        if (cmd == 1) {
            cin >> l >> r >> v;
            modify(l, r, v);
        } else {
            cin >> l >> r;
            cout << query(l, r) << endl;
        }
    }
}

/*
10
1 0 3 3
0 0 5
1 2 4 2
0 0 5
*/