#include <bits/stdc++.h>

using namespace std;

using pi4 = tuple<int, int, int, int>;

vector<int> G[101010], A;

int L[101010], N[101010];

int D[101010][4];

bitset<101010> C;

int n, m, dn;

int dfs1(int u, int p) {

    L[u] = N[u] = ++dn;

    for (int v : G[u]) {

        if (!N[v]) {

            L[u] = min(L[u], dfs1(v, u));

        } else if (v != p) {

            L[u] = min(L[u], N[v]);

        }

    }

    return L[u];

}

pi4 dfs2(int u, int p) {

    auto &[v00, v01, v10, v11] = D[u];

    v00 = 0, v01 = (L[u] <= N[u]), v10 = 0, v11 = 1;

    C[u] = 1;

    for (int v : G[u]) {

        if (!C[v]) {

            auto [t00, t01, t10, t11] = dfs2(v, u);

            if (L[v] >= N[u]) {

                int t = max({t00, t01, t10, t11});

                v00 += t;

                v10 += t;

                v01 += t00;

                v11 += t00;

            } else {

                v00 += max(t01, t00);

                v10 += max(t11, t10);

                v01 += t00;

                v11 += t10;

            }

        } else if (v != p && N[v] < N[u]) {

            v01--;

        }

    }

    return {v00, v01, v10, v11};

}

void dfs3(int u, int p, int k) {

    C[u] = 0;

    for (int v : G[u]) {

        if (C[v]) {

            if (L[v] >= N[u]) {

                if (k & 1) {

                    dfs3(v, u, 0);

                } else {

                    dfs3(v, u, max_element(D[v], D[v] + 4) - D[v]);

                }

            } else {

                int t;

                if (k == 0) {

                    t = D[v][0] >= D[v][1] ? 0 : 1;

                } else if (k == 2) {

                    t = D[v][2] >= D[v][3] ? 2 : 3;

                } else if (k == 1) {

                    t = 0;

                } else {

                    t = 2;

                }

                dfs3(v, u, t);

            }

        }

    }

    if (k & 1) {

        A.push_back(u);

    }

}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {

        int u, v;

        cin >> u >> v;

        G[u].push_back(v);

        G[v].push_back(u);

    }

    dfs1(1, 0);

    dfs2(1, 0);

    dfs3(1, 0, max_element(D[1], D[1] + 4) - D[1]);

    sort(A.begin(), A.end());

    cout << A.size() << "\n";

    for (int u : A) {

        cout << u << " ";

    }

    cout << "\n";

    return 0;

}