#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazySeg {
    vector<ll> tree, lazy;
    int size;

    LazySeg(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size);
        lazy.resize(2 * size);
    }

    void propagate(int node, int s, int e) {
        if (!lazy[node]) return;
        tree[node] += (e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(int node, int s, int e, int l, int r, ll v) {
        propagate(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            tree[node] += (e - s + 1) * v;
            if (s != e) {
                lazy[node * 2] += v;
                lazy[node * 2 + 1] += v;
            }
            return;
        }
        int m = s + e >> 1;
        update(node * 2, s, m, l, r, v);
        update(node * 2 + 1, m + 1, e, l, r, v);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int node, int s, int e, int x) {
        propagate(node, s, e);
        if (x < s || e < x) return 0;
        if (s == e) return tree[node];
        int m = s + e >> 1;
        return query(node * 2, s, m, x) + query(node * 2 + 1, m + 1, e, x);
    }

    void update(int a, int b, ll c) {
        update(1, 1, size, a, b, c);
    }

    ll query(int x) {
        return query(1, 1, size, x);
    }
};

struct Seg {
    vector<int> tree;
    int bias;

    Seg(int n) {
        bias = 1;
        while (bias < n) bias <<= 1;
        tree.resize(2 * bias);
    }

    void update(int x, int v) {
        tree[x += bias] = v;
        while (x >>= 1) {
            tree[x] = __gcd(tree[x << 1], tree[x << 1 | 1]);
        }
    }

    ll query(int l, int r) {
        l += bias, r += bias;
        int ret = 0;
        while (l < r) {
            if (l & 1) ret = __gcd(ret, tree[l++]);
            if (!(r & 1)) ret = __gcd(ret, tree[r--]);
            l >>= 1, r >>= 1;
        }
        if (l == r) ret = __gcd(ret, tree[r]);
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    LazySeg bit(n);
    for (int i = 1; i <= n; i++) {
        ll t;
        cin >> t;
        bit.update(i, i, t);
    }

    Seg seg(n);
    for (int i = 1; i < n; i++) {
        ll now = bit.query(i) - bit.query(i + 1);
        seg.update(i, abs(now));
    }

    int m;
    cin >> m;
    while (m--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 0) {
            ll now = seg.query(a, b - 1);
            now = __gcd(now, bit.query(a));
            cout << now << "\n";
        } else {
            bit.update(a, b, op);
            ll now = bit.query(a - 1) - bit.query(a);
            seg.update(a - 1, abs(now));
            now = bit.query(b) - bit.query(b + 1);
            seg.update(b, abs(now));
        }
    }
    return 0;
}