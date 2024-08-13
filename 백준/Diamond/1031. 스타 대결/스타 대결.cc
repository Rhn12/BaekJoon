#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> jimin(n), hansu(m);
    vector<string> table(n, string(m, '0'));
    vector<int> constraint(m, 0);

    int diff = 0;
    
    for (int &j : jimin) {
        cin >> j;
        if (j > m) {
            cout << -1;
            return 0;
        }
        diff += j;
        for (int y = 0; y < j; ++y) {
            constraint[y]++;
        }
    }

    for (int &h : hansu) {
        cin >> h;
        if (h > n) {
            cout << -1;
            return 0;
        }
        diff -= h;
    }

    if (diff) {
        cout << -1;
        return 0;
    }

    vector<int> sorted_hansu = hansu;
    sort(sorted_hansu.begin(), sorted_hansu.end(), greater<int>());

    for (int y = 0; y < m; ++y) {
        if ((diff += sorted_hansu[y] - constraint[y]) > 0) {
            cout << -1;
            return 0;
        }
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < jimin[x]; ++y) {
            constraint[y]--;
        }

        for (int y = 0; y < m; ++y) {
            sorted_hansu[y] = hansu[y];
        }
        sort(sorted_hansu.begin(), sorted_hansu.end(), greater<int>());

        for (int y = 0; y < m; ++y) {
            if ((diff += sorted_hansu[y] - constraint[y]) > 0) {
                for (int j = m - 1; diff > 0; --j) {
                    if (hansu[j] >= sorted_hansu[y] && table[x][j] == '0') {
                        table[x][j] = '1';
                        jimin[x]--;
                        hansu[j]--;
                        diff--;
                    }
                }
            }
        }
    }

    for (const auto& row : table) {
        cout << row << '\n';
    }

    return 0;
}