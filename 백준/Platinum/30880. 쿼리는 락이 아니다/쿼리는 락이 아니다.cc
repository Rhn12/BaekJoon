#include <bits/stdc++.h>

using namespace std;

constexpr long long mod = 1e9 + 7;

struct SegTree {
    struct Node {
        long long _, _r, _ro, _roc, _rock;
        long long o, c, k, oc, ck, ock;

        void apply(const char& ch) {
            _ = 2ll;
            _r = _ro = _roc = _rock = 0ll;
            o = c = k = oc = ck = ock = 0ll;
            if (ch == 'R') {
                _r = 1ll;
            } else if (ch == 'O') {
                o = 1ll;
            } else if (ch == 'C') {
                c = 1ll;
            } else if (ch == 'K') {
                k = 1ll;
            }
        }
    };

    Node unite(const Node& a, const Node& b) {
        Node res;
        res._ = a._ * b._ % mod;
        res._r = (a._r + a._ * b._r) % mod;
        res._ro = (a._ro + a._r * b.o + a._ * b._ro) % mod;
        res._roc = (a._roc + a._ro * b.c + a._r * b.oc + a._ * b._roc) % mod;
        res._rock = (a._rock + a._roc * b.k + a._ro * b.ck + a._r * b.ock + a._ * b._rock) % mod;
        res.o = (a.o + b.o) % mod;
        res.c = (a.c + b.c) % mod;
        res.k = (a.k + b.k) % mod;
        res.oc = (a.oc + a.o * b.c + b.oc) % mod;
        res.ck = (a.ck + a.c * b.k + b.ck) % mod;
        res.ock = (a.ock + a.oc * b.k + a.o * b.ck + b.ock) % mod;
        return res;
    }

    int n;
    vector<Node> tree;

    void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    void build(int x, int l, int r, const string& s) {
        if (l == r) {
            tree[x].apply(s[l]);
            return;
        }
        int y = l + r >> 1;
        int z = x + (y - l + 1 << 1);
        build(x + 1, l, y, s);
        build(z, y + 1, r, s);
        pull(x, z);
    }

    SegTree(const string& s) {
        n = (int) s.length();
        tree.resize(n + n - 1);
        build(0, 0, n - 1, s);
    }

    void ut(int x, int l, int r, int p, char c) {
        if (l == r) {
            tree[x].apply(c);
            return;
        }
        int y = l + r >> 1;
        int z = x + (y - l + 1 << 1);
        if (p <= y) {
            ut(x + 1, l, y, p, c);
        } else {
            ut(z, y + 1, r, p, c);
        }
        pull(x, z);
    }

    void ut(int p, char c) {
        ut(0, 0, n - 1, p, c);
    }

    Node get(int x, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return tree[x];
        }
        int y = l + r >> 1;
        int z = x + (y - l + 1 << 1);
        if (rr <= y) {
            return get(x + 1, l, y, ll, rr);
        }
        if (y < ll) {
            return get(z, y + 1, r, ll, rr);
        }
        return unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
    }

    long long get(int ll, int rr) {
        return get(0, 0, n - 1, ll, rr)._rock;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    SegTree segtree(s);

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int idx;
            char c;
            cin >> idx >> c;
            segtree.ut(--idx, c);
        } else {
            int l, r;
            cin >> l >> r;
            cout << segtree.get(--l, --r) << "\n";
        }
    }

    return 0;
}