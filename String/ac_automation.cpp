const int K = 26,MAXN = 100005;;
struct Trie {
    int nxt[K], go[K], pid, pch, leaf = -1, link = -1, lst = -1;
    Trie (int _pid=0, int _pch=0) {
        memset(nxt, -1, sizeof(nxt));
        memset(go, -1, sizeof(go));
        pid = _pid;
        pch = _pch;
    }
};
vector<Trie> trie(1);
vector<int> occ[MAXN];

void addString (string &str, int id) {
    int nd = 0;
    for (auto c : str) {
        int cid = c - 'a';
        if (trie[nd].nxt[cid] == -1) {
            trie[nd].nxt[cid] = SZ(trie);
            trie.emplace_back(nd, cid);
        }
        nd = trie[nd].nxt[cid];
    }
    trie[nd].leaf = id;
}

int go (int nd, int cid);

int getLink (int nd) {
    if (trie[nd].link == -1) {
        if (nd == 0 || trie[nd].pid == 0) {
            trie[nd].link = 0;
        } else {
            trie[nd].link = go(getLink(trie[nd].pid), trie[nd].pch);
        }
    }
    return trie[nd].link;
}

int getLast (int nd) {
    if (trie[nd].lst == -1) {
        if (trie[getLink(nd)].leaf == -1) {
            trie[nd].lst = nd == 0 ? 0 : getLast(getLink(nd));
        } else {
            trie[nd].lst = getLink(nd);
        }
    }
    return trie[nd].lst;
}

int go (int nd, int cid) {
    if (trie[nd].go[cid] == -1) {
        if (trie[nd].nxt[cid] != -1) {
            trie[nd].go[cid] = trie[nd].nxt[cid];
        } else {
            trie[nd].go[cid] = nd == 0 ? 0 : go(getLink(nd), cid);
        }
    }
    return trie[nd].go[cid];
}

void query (string &str) {
    int nd = 0;
    int sid = 0;
    for (auto c : str) {
        int cid = c - 'a';
        nd = go(nd, cid);

        int ptr = nd;
        while (ptr != 0) {
            if (trie[ptr].leaf != -1) {
                occ[trie[ptr].leaf].emplace_back(sid);
            }
            ptr = getLast(ptr);
        }

        sid++;
    }
}