template <typename pNode>
struct Emap {
    vector<map<int, pNode> > data;
    inline void init(int n) { data.resize(n); }
    inline pNode& operator[](const pii p) { return data[p.ff][p.ss]; }
    inline bool has(const pii p) { return data[p.ff].find(p.ss) != data[p.ff].end(); }
    inline void erase(const pii p) { data[p.ff].erase(p.ss); }
};

class ETT {
public:
    int n, llv;

private:
    struct Node;
    typedef Node* pNode;
    typedef pair<pNode, pNode> ppN;

    static int size(pNode p) { return p ? p->sz : 0; }

    struct Node {
        pii e;
        pNode L = NULL, R = NULL, P = NULL;
        int sz = 1;
        int llv;
        set<int> Edges[2];
        bool hasE[2] = {};
        inline bool isLeft() { return P && P->L == this; }
        inline bool isRight() { return P && P->R == this; }
        inline bool isRoot() { return !isLeft() && !isRight(); }
        inline pNode& get(bool i) { return !i ? L : R; } // 0 - LEFT
        inline pNode setCH(bool i, pNode ch) {
            ch->P = this;
            get(i) = ch;
            return this;
        }
        inline pNode getLast() { return R ? R->getLast() : this; }
        inline pNode up() {
            sz = 1 + size(L) + size(R);
            for (int i = 0; i < 2; i++) {
                hasE[i] = !Edges[i].empty();
                if (L)
                    hasE[i] |= L->hasE[i];
                if (R)
                    hasE[i] |= R->hasE[i];
            }
            return this;
        }
        Node(pii p, int l) : e{ p }, llv{ l } {}
        pNode find_first(bool lt) {
            if (L && L->hasE[lt])
                return L->find_first(lt);
            if (!Edges[lt].empty())
                return this;
            return R->find_first(lt);
        }
        inline void insertEdge(bool lt, int d) {
            splay();
            Edges[lt].insert(d);
            up();
        }
        inline void eraseEdge(bool lt, int d) {
            splay();
            Edges[lt].erase(d);
            up();
        }
        inline void rotate(const bool dir) {
            pNode x = get(!dir);
            get(!dir) = x->get(dir);
            x->get(dir) = this;
            x->P = P;
            if (P) {
                if (P->L == this) P->L = x;
                if (P->R == this) P->R = x;
            }
            P = x;
            if (get(!dir))
                get(!dir)->P = this;
            up();
            x->up();
        }
        inline void rotateTop() { P->rotate(isLeft()); }
        inline void splay(pNode rt = NULL) {
            while (P != rt) {
                if (P->P != rt)
                    ((P->isLeft() == isLeft()) ? P : this)->rotateTop();
                rotateTop();
            }
        }
    };
    pNode setFirst(pNode p) {
        if (!p) return p;
        p->splay();
        if (!p->R) swap(p->R, p->L); // , p->up();
        else if (p->L) {
            p->getLast()->splay(p);
            p->R->setCH(1, p->L)->up();
            p->L = NULL;
            p->up();
        }
        return p;
    }
    Emap<pNode> Epos;
    vector<Node> Ppos;
    inline bool onSameTree(pNode a, pNode b) {
        return a && b && (a == b || (a->splay(), b->splay(), a->P));
    }
    inline pNode create(pii e) {
        return Epos.has(e) ? Epos[e] : Epos[e] = new Node(e, llv);
    }

public:
    ETT(int _n, int lv) : n{_n}, llv{lv} {
        Epos.init(n);
        for (int i = 0; i < n; i++)
            Ppos.emplace_back(make_pair(i, i), llv);
    }
    inline bool onSameTree(int a, int b) { return onSameTree(&Ppos[a], &Ppos[b]); }
    inline bool hasEdge(pii e) { return Epos.has(e); }
    inline void link(pii p) {
        pNode l = setFirst(&Ppos[p.ff]), r = setFirst(&Ppos[p.ss]);
        create(swp(p))->setCH(0, create(p)->setCH(0, l)->setCH(1, r)->up())->up();
    }
    int cnt = 0;
    inline void link(int a, int b) { link({ a, b }); }
    void cut(pii p) {
        if (!hasEdge(p))
            return;
        pNode fs = Epos[p], ls = Epos[swp(p)];
        setFirst(fs);
        if (fs->R)
            fs->R->P = NULL;
        fs->R = NULL;
        ls->splay();
        if (ls->L)
            ls->L->P = NULL;
        if (ls->R)
            ls->R->P = NULL;
        Epos.erase(p);
        Epos.erase(swp(p));
        delete fs;
        delete ls;
    }
    inline void cut(int a, int b) { cut({ a, b }); }
    inline int size(int a) { return Ppos[a].splay(), (Ppos[a].sz + 2) / 3; }
    inline void addEdge(bool lt, pii e) {
        Ppos[e.ff].insertEdge(lt, e.ss);
        Ppos[e.ss].insertEdge(lt, e.ff);
        if (lt)
            link(e);
    }
    inline void remEdge(bool lt, pii e, bool ct = true) {
        Ppos[e.ff].eraseEdge(lt, e.ss);
        Ppos[e.ss].eraseEdge(lt, e.ff);
        if (lt && ct)
            cut(e);
    }
    void forEach(bool lt, int start, function<bool(pii)> func) {
        Ppos[start].splay();
        for (pNode i = &Ppos[start]; i && i->hasE[lt]; i = i->R) {
            (i = i->find_first(lt))->splay();
            for (auto j : i->Edges[lt])
                if (func({ i->e.ff, j }))
                    return;
            i->splay();
        }
    }
};

struct DyG {
    vector<ETT> ETTs;
    map<pair<int, int>, int> lvl;
    int lgn, n;
    inline int& level(pii p) { return lvl[norm(p)]; }
    inline bool hasEdge(pii p) { return lvl.find(norm(p)) != lvl.end(); }
    inline void eraselvl(pii p) { lvl.erase(norm(p)); }
    DyG(int _n) : n{n}, lgn{__lg(n)} {
        for (int i = 0; i <= lgn; i++)
            ETTs.emplace_back(n, i);
    }
    inline bool isConnected(int a, int b) { return ETTs[lgn].onSameTree(a, b); }
    inline void decrlvl(bool lt, pii e, int l = -1) {
        int& lv = level(e);
        ETTs[lv].remEdge(lt, e, false);
        ETTs[--lv].addEdge(lt, e);
    }
    inline void add(int a, int b) {
        if (hasEdge({ a, b })) return;
        level({ a, b }) = lgn;
        ETTs[lgn].addEdge(!isConnected(a, b), { a, b });
    }
    void remove(pii e) {
        if (!hasEdge(e)) return;
        int l = level(e);
        eraselvl(e);
        bool hasEdge = ETTs[lgn].hasEdge(e);
        ETTs[l].remEdge(hasEdge, e);
        if (!hasEdge) return;
        for (int i = l; i <= lgn; i++) {
            ETTs[i].cut(e);
            if (ETTs[i].size(e.ff) > ETTs[i].size(e.ss))
                e = { e.ss, e.ff };
            set<pii> tobe;
            ETTs[i].forEach(true, e.ff, [&](pii p) {
                tobe.insert(norm(p));
                return false;
            });
            for (auto p : tobe)
                decrlvl(true, p, i);
            tobe.clear();
            pii ans = { -1, -1 };

            ETTs[i].forEach(false, e.ff, [&](pii p) {
                if (ETTs[i].onSameTree(p.ss, e.ss))
                    return ans = p, true;
                tobe.insert(norm(p));
                return false;
            });

            for (auto p : tobe)
                decrlvl(false, p, i);
            if (ans != (pii) { -1, -1 }) {
                ETTs[i].remEdge(false, ans);
                ETTs[i].addEdge(true, ans);
                for (int lv = i + 1; lv <= lgn; lv++)
                    ETTs[lv].cut(e), ETTs[lv].link(ans);
                return;
            }
        }
    }
    inline void remove(int a, int b) { remove({ a, b }); }
};
