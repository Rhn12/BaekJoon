#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
typedef long long ll;
typedef pair<ll, ll> p;

int tree[1 << 18];
const int sz = 1 << 17;

void update(int x, int v) {
    x += sz;
    tree[x] += v;
    while (x > 1) {
        x >>= 1;
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }
}

int query(int l, int r) {
    if (l > r) return 0;
    l += sz;
    r += sz;
    int ret = 0;
    while (l <= r) {
        if (l & 1) ret += tree[l++];
        if (!(r & 1)) ret += tree[r--];
        l >>= 1;
        r >>= 1;
    }
    return ret;
}

int n, k;
int a[101010], b[101010];
p v[101010];
ll ans;
vector<p> l, r;

void f(int s, int e) {
    if (s == e) return;
    int m = s + e >> 1, j = 0;
    int lsize = m - s + 1;
    int rsize = e - m;
    l.clear(); r.clear();
    l.reserve(lsize);
    r.reserve(rsize);
    for (int i = s; i <= m; i++) l.push_back(v[i]);
    for (int i = m + 1; i <= e; i++) r.push_back(v[i]);
    sort(all(l));
    sort(all(r));

    for (int i = 0; i < lsize; i++) {
        while (j < rsize && r[j].x < l[i].x) update(r[j++].y, 1);
        ans += query(1, l[i].y - k - 1);
        ans += query(l[i].y + k + 1, n);
    }
    for (int i = 0; i < j; i++) update(r[i].y, -1);
    f(s, m);
    f(m + 1, e);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        a[t] = i;
    }
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        b[t] = i;
    }
    for (int i = 1; i <= n; i++) v[a[i]] = {b[i], i};
    f(1, n);
    cout << ans;
    return 0;
}