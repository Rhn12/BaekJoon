#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
namespace Edmonds {
    const long long INF = 1e18;
    struct edge {
        int u, v;
        long long w;
        edge(int u, int v, long long w) : u(u), v(v), w(w) {}
    };
    long long solve(vector<edge>& _edges, int n, int r) {
        vector<edge> edges = _edges;
        long long ans = 0;
        while (true) {
            vector<long long> mn(n, INF);
            vector<int> grp(n, -1), par(n, 0);
            vector<bool> vis(n), fin(n);
            int nn = 0;
            for (auto& it : edges) {
                if (it.u == it.v) continue;
                if (it.w < mn[it.v]) {
                    mn[it.v] = it.w;
                    par[it.v] = it.u;
                }
            }
            for (int i = 0; i < n; i++) {
                if (i == r) continue;
                if (mn[i] == INF) return INF;
                ans += mn[i];
            }
            fin[r] = vis[r] = true;
            bool cycle = false;
            for (int i = 0; i < n; i++) {
                if (fin[i]) continue;
                int j = i;
                while (!vis[j]) {
                    vis[j] = true;
                    j = par[j];
                }
                if (!fin[j]) {
                    do {
                        fin[j] = true;
                        grp[j] = nn;
                        j = par[j];
                    } while (!fin[j]);
                    cycle = true;
                    nn++;
                }
                j = i;
                while (!fin[j]) {
                    fin[j] = true;
                    j = par[j];
                }
            }
            if (!cycle) break;
            for (int i = 0; i < n; i++)
                if (grp[i] == -1) grp[i] = nn++;
            for (auto& it : edges) {
                if (grp[it.u] != grp[it.v])
                    it.w -= mn[it.v];
                it.u = grp[it.u];
                it.v = grp[it.v];
            }
            r = grp[r];
            n = nn;
        }
        return ans;
    }
}
int main() {
    int n;
    scanf("%d", &n);

    int x[310], y[310], z[310][310];
    for (int i = 1; i <= n; i++)
        scanf("%d", &x[i]);

    vector<Edmonds::edge> edges;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &y[i]);
        edges.emplace_back(0, i, y[i]);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            scanf("%d", &z[i][j]);
            if (i != j)
                edges.emplace_back(i, j, z[i][j]);
        }
    long long res = Edmonds::solve(edges, n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int mn = y[i];
        for (int j = 1; j <= n; j++)
            mn = min(mn, z[j][i]);
        res += (long long)(x[i] - 1) * mn;
    }
    printf("%lld", res);
    return 0;
    
}