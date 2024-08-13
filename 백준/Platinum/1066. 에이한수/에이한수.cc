#include <iostream>
#include <cstring>
using namespace std;

const int MEM = 1006;
const int MOD = 1e9+7;

int n, k;
int dp[MEM][11][11][11];

int DP(int a, int b, int c, int d) {
    if (a == n) return !b;
    int& ret = dp[a][b][c][d];
    if (ret != -1) return ret;
    ret = 0;
    if (d < 10) {
        for (int i = c; i <= 9; i++) {
            if (c + d == i) ret += DP(a + 1, b, c + d, d);
            else ret += DP(a + 1, b - 1, i, 10);
            ret %= MOD;
        }
    } else {
        for (int i = c; i <= 9; i++) {
            ret += DP(a + 1, b, i, i - c);
            ret %= MOD;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> k;
    if (k > 9) {
        cout << 0;
        return 0;
    }

    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= 9; i++) {
        ans += DP(1, k - 1, i, 10);
        ans %= MOD;
    }
    cout << ans;

    return 0;
}