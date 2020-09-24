struct Node {
    int l, r;
    Node *lc, *rc;
    int mx;
};
Node *root[MAXN];

int qry (int l, int r, Node *nd) {
    if (!nd) {
        return 0;
    } else if (nd->l == l && r == nd->r) {
        return nd->mx;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return qry(l, r, nd->rc);
        } else if (r <= mid) {
            return qry(l, r, nd->lc);
        } else {
            return max(qry(l, mid, nd->lc), qry(mid, r, nd->rc));
        }
    }
}

void chg (int pos, int v, Node *nd) {
    if (nd->l == nd->r-1) {
        nd->mx = max(nd->mx, v);
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (pos >= mid) {
            if (!nd->rc) {
                nd->rc = new Node{mid, nd->r, nullptr, nullptr, 0};
            }
            chg(pos, v, nd->rc);
            nd->mx = max(nd->mx, nd->rc->mx);
        } else {
            if (!nd->lc) {
                nd->lc = new Node{nd->l, mid, nullptr, nullptr, 0};
            }
            chg(pos, v, nd->lc);
            nd->mx = max(nd->mx, nd->lc->mx);
        }
    }
}