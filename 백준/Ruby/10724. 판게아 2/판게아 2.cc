#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    Node *l, *r, *p;
    int sz;
    pii sum, val;
    bool flip;

    Node() : l(nullptr), r(nullptr), p(nullptr), sz(1), flip(false), sum({-1, 0}), val({-1, 0}) {}
};

struct LCT {
    Node tr[300005];

    void clear() {
        for (int i = 0; i <= 300000; ++i) tr[i] = Node();
    }

    inline bool isRoot(Node* x) const {
        return !x->p || (x != x->p->l && x != x->p->r);
    }

    inline void update(Node* x) {
        x->sz = 1;
        x->sum = x->val;
        if (x->l) {
            x->sz += x->l->sz;
            x->sum = max(x->sum, x->l->sum);
        }
        if (x->r) {
            x->sz += x->r->sz;
            x->sum = max(x->sum, x->r->sum);
        }
    }

    inline void propagate(Node* x) {
        if (!x->flip) return;
        swap(x->l, x->r);
        if (x->l) x->l->flip ^= 1;
        if (x->r) x->r->flip ^= 1;
        x->flip = 0;
    }

    inline void rotate(Node* x) {
        Node* p = x->p;
        if (x == p->l) {
            p->l = x->r;
            x->r = p;
            if (p->l) p->l->p = p;
        } else {
            p->r = x->l;
            x->l = p;
            if (p->r) p->r->p = p;
        }
        x->p = p->p;
        p->p = x;
        if (x->p) {
            if (p == x->p->l) x->p->l = x;
            else if (p == x->p->r) x->p->r = x;
        }
        update(p);
        update(x);
    }

    void splay(Node* x) {
        while (!isRoot(x)) {
            Node* p = x->p;
            if (!isRoot(p)) propagate(p->p);
            propagate(p);
            propagate(x);
            if (!isRoot(p)) {
                if ((x == p->l) == (p == p->p->l)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
        propagate(x);
    }

    void makeRoot(Node* x) {
        access(x);
        splay(x);
        x->flip ^= 1;
    }

    void access(Node* x) {
        splay(x);
        x->r = nullptr;
        update(x);
        for (Node* y = x; x->p; splay(x)) {
            y = x->p;
            splay(y);
            y->r = x;
            update(y);
        }
    }

    void link(Node* x, Node* p) {
        makeRoot(x);
        access(x);
        access(p);
        x->l = p;
        p->p = x;
        update(x);
    }

    void cut(Node* x) {
        access(x);
        if (x->l) x->l->p = nullptr;
        x->l = nullptr;
        update(x);
    }

    Node* getLCA(Node* x, Node* y) {
        access(x);
        access(y);
        splay(x);
        return x->p ? x->p : x;
    }

    pii pathQuery(Node* x, Node* y) {
        Node* p = getLCA(x, y);
        access(x);
        splay(p);
        pii res = p->val;
        if (p->r) res = max(res, p->r->sum);
        access(y);
        splay(p);
        if (p->r) res = max(res, p->r->sum);
        return res;
    }

    Node* getRoot(Node* x) {
        access(x);
        while (x->l) x = x->l;
        splay(x);
        return x;
    }

    Node* getParent(Node* x) {
        access(x);
        propagate(x);
        if (!x->l) return nullptr;
        x = x->l;
        for (propagate(x); x->r; propagate(x)) x = x->r;
        access(x);
        return x;
    }

    inline void link(int x, int p) {
        link(tr + x, tr + p);
    }

    inline void cut(int x) {
        cut(tr + x);
    }

    void cut(int x, int y) {
        if (getParent(tr + x) == tr + y) cut(tr + x);
        else cut(tr + y);
    }

    inline int getLCA(int x, int y) {
        return getLCA(tr + x, tr + y) - tr;
    }

    inline pii pathQuery(int x, int y) {
        return pathQuery(tr + x, tr + y);
    }

    inline void update(int x, pii v) {
        access(tr + x);
        (tr + x)->val = v;
        update(tr + x);
    }

    inline int getRoot(int x) {
        return getRoot(tr + x) - tr;
    }

    int getParent(int x) {
        Node* p = getParent(tr + x);
        return (!p ? -1 : p - tr);
    }

    inline void makeRoot(int x) {
        makeRoot(tr + x);
    }
};

LCT lct;
pii edge[300005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T, n, q, cnt;
    ll sum, ans;
    cin >> T;
    while (T--) {
        lct.clear();
        sum = ans = 0;
        cin >> n >> q;
        cnt = n;
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            lct.link(a, cnt);
            lct.link(i, cnt);
            edge[cnt] = {a, i};
            sum += b;
            lct.update(cnt, {b, cnt});
            ++cnt;
        }
        for (int i = 0; i < q; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            pii p = lct.pathQuery(a, b);
            if (p.fi > c && a != b) {
                pii tmp = edge[p.se];
                lct.cut(tmp.fi, p.se);
                lct.cut(tmp.se, p.se);
                lct.link(a, cnt);
                lct.link(b, cnt);
                lct.update(cnt, {c, cnt});
                edge[cnt] = {a, b};
                ++cnt;
                sum += c - p.fi;
            }
            ans ^= sum;
        }
        cout << ans << '\n';
    }
    return 0;
}