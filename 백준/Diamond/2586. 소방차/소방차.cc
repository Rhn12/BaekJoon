#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll    long long
using namespace std;

int n, m;

ll p[101010]; ll f[101010];

bool dp[101010];

ll dy[101010][3];

ll solve() {

    ll res = 0;        

    for (int i = 1; i <= m; i++) {

        int ub = int(upper_bound(p, p + n, f[i]) - p);

        int node; if (abs(p[ub] - f[i]) > abs(p[ub - 1] - f[i])) node = ub - 1;

        else node = ub;

        if (!dp[node]) {

            dp[node] = true;

            res += abs(p[node] - f[i]);

        }

        else {

            ll cnt = 0;

            for (int j = node; j >= 1; j--) {

                if (dp[j]) cnt++;

                else break;

            }

            if (node - cnt == 0) {

                cnt = 0;

                for (int j = node; j <= m; j++) {

                    if (dp[j]) cnt++;

                    else break;

                }

                dp[node + cnt] = true;

                res += abs(p[node + cnt] - f[i]);

                continue;

            }

            else {

                ll add = 0;    ll push = 0;

                int ccnt = 0;

                for (int j = node + 1; ; j++) {

                    if (dp[j]) node++;

                    else break;

                }

                for (int j = node; j >= 1; j--) {

                    if (dp[j]) {

                        add += abs(p[j] - f[i - node + j - 1]);

                        push += abs(p[j - 1] - f[i - node + j - 1]);

                        ccnt++;

                    }

                    else break;

                }

                push += abs(p[node] - f[i]);

                if (add + abs(p[node + 1] - f[i]) >= push) {

                    res -= add;

                    dp[node - ccnt] = true;

                    res += push;

                }

                else {

                    ccnt = 0;

                    for (int s = node; ; s++) {

                        if (dp[s]) ccnt++;

                        else break;

                    }

                    dp[node + ccnt] = true;

                    res += abs(p[node + ccnt] - f[i]);

                }

            }

        }

    }

    return res;

}

ll dynamicprogramming() {

    ll res = 0;

    for (int i = 1; i <= m; i++) {

        int ub = int(upper_bound(p, p + n, f[i]) - p);

        int node; if (abs(p[ub] - f[i]) > abs(p[ub - 1] - f[i])) node = ub - 1;

        else node = ub;

        if (!dp[node]) {

            dp[node] = true;

            res += abs(p[node] - f[i]);

        }

        else {

            ll cnt = 0;

            for (int j = node; j >= 1; j--) {

                if (dp[j]) cnt++;

                else break;

            }

            if (node - cnt == 0) {

                cnt = 0;

                for (int j = node; j <= m; j++) {

                    if (dp[j]) cnt++;

                    else break;

                }

                dp[node + cnt] = true;

                res += abs(p[node + cnt] - f[i]);

                continue;

            }

            else {

                ll add = 0;

                int ccnt = 0;

                for (int j = node; j >= 1; j--) {

                    if (dp[j]) {

                        add += abs(p[j] - f[i - node + j - 1]);

                        ccnt++;

                    }

                    else break;

                }

 

                ll push = 0;

                for (int j = node; j >= 1; j--) {

                    if (dp[j]) {

                        push += abs(p[j - 1] - f[i - node + j - 1]);

                    }

                    else break;

                }

                push += abs(p[node] - f[i]);

                if (add + abs(p[node + 1] - f[i]) >= push) {

                    res -= add;

                    dp[node - ccnt] = true;

                    res += push;

                }

                else {

                    dp[node + 1] = true;

                    res += abs(p[node + 1] - f[i]);

                }

            }

        }

    }

    return res; 

}

 

void input() {

    scanf("%d %d", &n, &m); p[0] = -2147483647; f[0] = -2147483647;

    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);

    for (int i = n + 1; i <= 100010; i++) p[i] = 2147483647;

    for (int j = 1; j <= m; j++) scanf("%d", &f[j]);

    for (int j = m + 1; j <= 100010; j++) f[j] = 2147483647;

}

 

int main() {

    input();

    printf("%lld\n", solve());

    return 0;

}