#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
const char nl = '\n';
using namespace std;
using ll = long long;
using ld = long double;
const int N = 1e5+1;

int h[N];
int ans[N];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> h[i];
  int q; cin >> q;
  vector<vector<tuple<int, int, int>>> qs(n+1);
  for (int i = 0; i < q; i++) {
    int l, r, w; cin >> l >> r >> w; l--; r--;
    qs[w].emplace_back(l, r, i);
  }
  for (int w = 1; w <= n; w++) {
    for (auto [l, r, i] : qs[w]) {
      int cur = 0;
      for (int k = l; k <= r-w+1; k++) {
        cur = max(cur, h[k]);
      }
      ans[i] = cur;
    }
    for (int k = 0; k < n-w; k++) {
      h[k] = min(h[k], h[k+1]);
    }
  }
  for (int i = 0; i < q; i++) cout << ans[i] << nl;
}