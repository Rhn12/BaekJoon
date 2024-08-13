#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

const int MAXN = (50000 + 63) / 64 + 1;
uint64_t appearances[26][MAXN];
uint64_t ans[MAXN];

void getlastrow(vector<int>& ret, const string& a, const string& b) {
    int m = a.size();
    int n = b.size();
    int numwords = (m + 63) / 64;

    memset(appearances, 0, sizeof(appearances));
    memset(ans, 0, sizeof(ans));

    for(int i = 0; i < m; i++) {
        appearances[a[i] - 'A'][i / 64] |= (1ULL << (i % 64));
    }

    for(int i = 0; i < n; i++) {
        uint64_t b1 = 1;
        uint64_t b2 = 0;
        for(int j = 0; j < numwords; j++) {
            uint64_t U = ans[j] | appearances[b[i] - 'A'][j];
            uint64_t c = ans[j] >> 63;
            uint64_t V = U - (ans[j] << 1 | (b1 | b2));
            b1 = c;
            b2 = (V > U ? 1 : 0);
            ans[j] = U & (~V);
        }
    }

    ret.resize(m + 1);
    int amt = 0;
    for(int i = 0; i < m; i++) {
        amt += (bool)(ans[i / 64] & (1ULL << (i % 64)));
        ret[i + 1] = amt;
    }
}

void getans(string& ret, const string& a, const string& b) {
    if(a.empty() || b.empty()) return;
    if(a.size() == 1) {
        if(b.find(a[0]) != string::npos) {
            ret += a[0];
        }
        return;
    }
    if(b.size() == 1) {
        if(a.find(b[0]) != string::npos) {
            ret += b[0];
        }
        return;
    }

    int amid = a.size() / 2;
    string br = b;
    reverse(br.begin(), br.end());
    string alhs = a.substr(0, amid);
    string arhs = a.substr(amid);
    reverse(arhs.begin(), arhs.end());

    vector<int> lhsscore, rhsscore;
    getlastrow(lhsscore, b, alhs);
    getlastrow(rhsscore, br, arhs);
    reverse(arhs.begin(), arhs.end());

    int ybest = 0;
    for(int i = 1; i < lhsscore.size(); i++) {
        int cand = lhsscore[i] + rhsscore[rhsscore.size() - 1 - i];
        if(cand > lhsscore[ybest] + rhsscore[rhsscore.size() - 1 - ybest]) {
            ybest = i;
        }
    }

    string lhsret, rhsret;
    string blhs = b.substr(0, ybest);
    string brhs = b.substr(ybest);
    getans(lhsret, alhs, blhs);
    getans(rhsret, arhs, brhs);
    ret += lhsret;
    ret += rhsret;
}

void solve() {
    string a, b;
    cin >> a >> b;
    string ret;
    getans(ret, a, b);
    cout << ret.size() << "\n";
    cout << ret << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}