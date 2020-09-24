struct Nd{
    int pri = rand();
    int val = 0, tag = 0, id = 0, idtg = 0, mx=0;
    Nd * lc=0, *rc = 0;
    Nd(int v, int pos) {
        val = mx=v; id = pos;
    }
};

inline void push(Nd *& o) {
    if (!o) return;
    if (o->tag) {
        o->val += o->tag;
        o->mx += o->tag;
        if (o->lc) o->lc->tag += o->tag;
        if (o->rc) o->rc->tag += o->tag;
        o->tag=0;
    }
    if (o->idtg) {
        o->id += o->idtg;
        if (o->lc) o->lc->idtg += o->idtg;
        if (o->rc) o->rc->idtg += o->idtg;
        o->idtg = 0;
    }
}

inline void pull(Nd *&o) {
    if (!o)return;
    o->mx = o->val;
    if (o->lc) o->mx = max(o->mx, o->lc->mx);
    if (o->rc) o->mx = max(o->mx, o->rc->mx);
}

Nd * merge(Nd *&A, Nd*&B) {
    push(A); push(B);
    if (!A) return B;
    if (!B) return A;
    if (A->pri > B->pri) {
        A->rc = merge(A->rc, B);
        push(A->lc);
        pull(A);
        return A;
    }else{
        B->lc = merge(A, B->lc);
        push(B->rc);
        pull(B);
        return B;
    }
}

void split(Nd *o, Nd * & A, Nd *& B, int id) {
    A=B=0;
    if (!o) return;
    push(o);
    if (o -> id < id) {
        A = o;
        split(o->rc, A->rc, B, id);
        push(A->lc);
        pull(A);
    }else{
        B = o;
        split(o->lc,A, B->lc, id);
        push(B->rc);
        pull(B);
    }
}
