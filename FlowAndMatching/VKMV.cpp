const int MX = 507;
 
ll a[MX][MX];
 
using T = ll;
T hungary(int n, int m) { // N is size of left set, M is size of right set
    vector<T> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<T> minv (m + 1, INF);
        vector<char> used (m + 1, 0);
        while (p[j0] != 0) {
            used[j0] = 1;
            int i0 = p[j0], j1 = 0;
            T d = INF;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    T cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < d)
                        d = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += d, v[j] -= d;
                else
                    minv[j] -= d;
            j0 = j1;
        }
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
 
    vector<int> ans (n + 1);
    for (int j = 1; j <= m; ++j)
        ans[p[j]] = j;
    T cost = -v[0];
    return cost;
}
 
