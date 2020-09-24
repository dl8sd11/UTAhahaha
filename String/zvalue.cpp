#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000006;

int z[MAXN];
string a;
void init(string x) {
    a = x;
    std::memset(z, 0, sizeof z);
}
void z_build() {
    z[0] = 0;
    for (int i = 1, bst = 0; a[i]; i++) {
        if (bst + z[bst] < i) {
            z[i] = 0;
        } else {
            z[i] = min(z[i - bst], bst + z[bst] - i);
        }
        while (a[z[i]] == a[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] > bst + z[bst]) {
            bst = i;
        }
    }
}

int mat(string x,string y) {
    int ret = 0;
    init(x+'$'+y);
    z_build();
    for (int i=int(x.size())+1;i<=int(x.size()+y.size());i++) {
        ret +=  (z[i] == int(x.size()));
    }
    return ret;
}

int main () {
    string a, b;
    cout << mat(a, b) << endl;
}