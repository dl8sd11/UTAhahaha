
// Lower Hull
bool QTYPE=0;
struct Line {
    mutable ll m, b, p;
    bool operator<(const Line& o) const {
        if (QTYPE) return p<o.p;
        return m < o.m;
    }
};

struct LineContainer : multiset<Line > {
    // (for doubles, use INF = 1/.0, div(a,b) = a/b)
    const ll INF = LLONG_MAX;
    ll div(ll A, ll B) { // floored division
        return A / B - ((A ^ B) < 0 && A % B); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = INF; return false; }
        if (x->m == y->m) x->p = x->b > y->b ? INF : -INF;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        QTYPE=1; auto l = *lower_bound({0,0,x}); QTYPE = 0;
        return l.m * x + l.b;
    }
};
