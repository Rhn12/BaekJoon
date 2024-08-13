#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
string a, b;
ll h[2][7005], v[7005];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> a >> b;
    int n = a.size(), m = b.size();

    for (int j = 0; j <= m; j++) {
        h[0][j] = j;
    }
    for (int i = 0; i <= n; i++) {
        v[i] = 0;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] != b[j - 1]) {
                h[i % 2][j] = max(h[(i - 1) % 2][j], v[j - 1]);
                v[j] = min(h[(i - 1) % 2][j], v[j - 1]);
            } else {
                h[i % 2][j] = v[j - 1];
                v[j] = h[(i - 1) % 2][j];
            }
            ans += (j - h[i % 2][j]) * (m - j + 1);
        }
    }
    cout << ans << "\n";
    return 0;
}