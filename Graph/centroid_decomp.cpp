int n;
vector<vector<pii> > edge;
struct CentroidDecomp {
    struct Info {
        ll dis=0, sz=0, mi=0;
    };
    vector<Info> info;
    vector<int> dead, dep, anc, vis, sz;
    vector<vector<ll> > dis;

    CentroidDecomp () : info(n), dead(n), dep(n), anc(n), vis(n), sz(n) {
        int lgg = __lg(n) + 2;
        dis.resize(lgg, vector<ll>(n, 0));
        build(0, 0, -1);
    }

    int center (int nd) {
        vector<int> que = {nd};
        vis[nd] = true;
        int hd = 0;
        while (hd < SZ(que)) {
            int cur = que[hd++];
            for (auto e : edge[cur]) {
                if (!vis[e.X] && !dead[e.X]) {
                    que.eb(e.X);
                    vis[e.X] = true;
                }
            }
        }
        reverse(ALL(que));

        int cen = -1;
        for (int v : que) {
            sz[v] = 1;
            vis[v] = false;
            bool flag = true;
            for (auto e : edge[v]) {
                if (!dead[e.X] && !vis[e.X]) {
                    sz[v] += sz[e.X];
                    flag &= sz[e.X] * 2 <= SZ(que);
                }
            }
            flag &= sz[v] * 2 >= SZ(que);
            if (flag) cen = v;
        }
        return cen;
    }

    void build (int nd, int d, int rt) {
        int cen = center(nd);
        assert(cen != -1);
        dead[cen] = true;
        dep[cen] = d;
        anc[cen] = rt;

        vector<int> que = {cen};
        int hd = 0;
        while (hd < SZ(que)) {
            int cur = que[hd++];
            for (auto e : edge[cur]) {
                if (!vis[e.X] && !dead[e.X]) {
                    que.eb(e.X);
                    vis[e.X] = true;
                    dis[d][e.X] = dis[d][cur] + e.Y;
                }
            }
        }
        for (int v : que) vis[v] = false;

        for (auto e : edge[cen]) {
            if (!dead[e.X]) {
                build(e.X, d+1, cen);
            }
        }
    }

    void upd (int nd) {
        for (int x=nd; x!=-1; x=anc[x]) {
            info[x].dis += dis[dep[x]][nd];
            info[x].sz += 1;
            if (anc[x] != -1) info[x].mi += dis[dep[x]-1][nd];
        }
    }

    ll qry (int nd) {
        ll res = info[nd].dis;
        for (int x=nd; anc[x]!=-1; x=anc[x]) {
            res += dis[dep[x]-1][nd] * (info[anc[x]].sz - info[x].sz);
            res += info[anc[x]].dis;
            res -= info[x].mi;
        }
        return res;
    }
};
