#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 11092019;
const int MAX_N = 1e6 + 5;

vector<int> label(MAX_N), dp(MAX_N), cnt(MAX_N);
vector<vector<int>> adj(MAX_N);
vector<pair<int, int>> piles[MAX_N];

int curPiles = 0;

void dfs(int node) {
    int lo = 1, hi = curPiles;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (!piles[mid].empty() && piles[mid].back().first > label[node]) {
            dp[node] = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (dp[node] == 0) ++curPiles, dp[node] = curPiles;

    int ans = -1;
    if (dp[node] != 1) {
        lo = 0, hi = piles[dp[node] - 1].size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (piles[dp[node] - 1][mid].first > label[node]) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (ans == -1) {
            cnt[node] = piles[dp[node] - 1].back().second;
        } else {
            cnt[node] = (piles[dp[node] - 1].back().second - piles[dp[node] - 1][ans].second + MOD) % MOD;
        }
    } else {
        cnt[node] = 1;
    }

    int pilePrefix = (piles[dp[node]].empty() ? 0 : piles[dp[node]].back().second);
    piles[dp[node]].emplace_back(label[node], (pilePrefix + cnt[node]) % MOD);

    for (int v : adj[node]) dfs(v);

    piles[dp[node]].pop_back();
    if (piles[dp[node]].empty()) --curPiles;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> label[i];
    for (int i = 1; i < n; ++i) {
        int a;
        cin >> a;
        adj[a - 1].push_back(i);
    }

    dfs(0);

    int maxDp = 0, maxCnt = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > maxDp) {
            maxDp = dp[i];
            maxCnt = cnt[i];
        } else if (dp[i] == maxDp) {
            maxCnt = (maxCnt + cnt[i]) % MOD;
        }
    }

    cout << maxDp << ' ' << maxCnt << '\n';

    return 0;
}