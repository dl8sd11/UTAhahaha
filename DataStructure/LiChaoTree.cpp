struct Vec {
    ll x, y;
    ll eval (ll pos) {
        return pos*x + y;
    }
};

struct Node {
    int l, r;
    Node *lc, *rc;
    Vec bst;

    Node (int _l, int _r) : l(_l), r(_r) {
        lc = rc = nullptr;
        bst = {0, INF};
    }
};
Node *root[MAXN];

Node *addLine (Vec nw, Node *nd) {
    int mid = (nd->l + nd->r) >> 1;
    bool lnw = nw.eval(nd->l) < nd->bst.eval(nd->l);
    bool mnw = nw.eval(mid) < nd->bst.eval(mid);

    Node *ret = new Node(*nd);
    if (mnw) {
        swap(nw, ret->bst);
    }
    if (ret->l == ret->r - 1) {
        return ret;
    } else if (lnw != mnw) { // left
        if (!ret->lc) {
            ret->lc = new Node(ret->l, mid);
        }
        ret->lc = addLine(nw, ret->lc);
    } else {
        if (!ret->rc) {
            ret->rc = new Node(mid, ret->r);
        }
        ret->rc = addLine(nw, ret->rc);
    }

    return ret;
}

ll eval (ll x, Node *nd) {
    if (!nd) {
        return INF;
    }
    ll ret = nd->bst.eval(x);
    int mid = (nd->l + nd->r) >> 1;
    if (x >= mid) {
        ret = min(ret, eval(x, nd->rc));
    } else {
        ret = min(ret, eval(x, nd->lc));
    }
    return ret;
}