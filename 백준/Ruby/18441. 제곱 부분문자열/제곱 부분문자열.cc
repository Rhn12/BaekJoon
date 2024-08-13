#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

void solve(int t, const string& a) {
    int n = a.size();
    vector<vector<int>> ih(2, vector<int>(n + 1));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    int ans = 0;
    int idx = 0;

    for (int i = 1; i <= n; i++) ih[0][i] = i;

    for (int i = 1, x = 1; i <= n; i++, x ^= 1) {
        int iv = 0, cur = 0;
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == a[j - 1]) {
                ih[x][j] = iv;
                iv = ih[x ^ 1][j];
            } else {
                ih[x][j] = max(ih[x ^ 1][j], iv);
                iv = min(ih[x ^ 1][j], iv);
            }

            if (j > i && ih[x][j] <= i) cur++;
        }

        if (cur > ans) {
            ans = cur;
            idx = i;
        }
    }

    if (ans == 0) {
        cout << "Case #" << t << ": 0\n";
        return;
    }

    int x = idx, y = n - idx;
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            if (a[i - 1] == a[idx + j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string rans(ans, ' ');
    while (x > 0 && y > 0) {
        if (a[x - 1] == a[idx + y - 1]) {
            rans[dp[x][y] - 1] = a[x - 1];
            --x;
            --y;
        } else if (dp[x][y] == dp[x - 1][y]) {
            --x;
        } else {
            --y;
        }
    }

    cout << "Case #" << t << ": " << ans * 2 << "\n";
    cout << rans << rans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        string a;
        cin >> a;
        solve(i, a);
    }
    return 0;
}