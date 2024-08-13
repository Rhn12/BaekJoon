#pragma GCC optimize("O3")

#pragma GCC optimize("unroll-loops")

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")

#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int n, s;

bool vis[N], ok[N];

vector<int> g[N], V, ans;

queue<int> que;

void dfs(int u) {

    vis[u] = true;

    for (int v : g[u]) {

        if (!vis[v]) dfs(v);

    }

}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    

    cin >> n;

    for (int u = 1; u <= n; ++u) {

        int k;

        cin >> k;

        g[u].resize(k);

        for (int i = 0; i < k; ++i) {

            cin >> g[u][i];

        }

    }

    

    // Finding a node 's' that can reach all other nodes in its component

    for (int u = 1; u <= n; ++u) {

        if (!vis[u]) {

            s = u;

            dfs(u);

        }

    }

    

    ok[s] = true;

    que.push(s);

    for (int i = 1; i <= n; ++i) {

        if (i != s) V.push_back(i);

    }

    

    while (!que.empty()) {

        int u = que.front();

        que.pop();

        vector<int> NV;

        int i = 0;

        for (int v : V) {

            while (i < g[u].size() && g[u][i] < v) ++i;

            if (i < g[u].size() && v == g[u][i]) {

                NV.push_back(v);

            } else {

                ok[v] = true;

                que.push(v);

            }

        }

        V.swap(NV);

    }

    

    for (int i = 1; i <= n; ++i) {

        if (ok[i]) ans.push_back(i);

    }

    

    cout << ans.size();

    for (int x : ans) cout << ' ' << x;

    cout << '\n';

    

    return 0;

}