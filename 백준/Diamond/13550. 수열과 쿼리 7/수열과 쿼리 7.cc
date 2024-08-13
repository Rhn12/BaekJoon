#include <bits/stdc++.h>
using namespace std;

const int SQRTN = 400;
const int MAXN = 1010101;
const int MAXQ = 1010101 / SQRTN + 10;

struct Query {
    int s, e, x;
    Query() {}
    Query(int s, int e, int x) : s(s), e(e), x(x) {}
    bool operator < (const Query &t) const {
        if (s / SQRTN != t.s / SQRTN) return s < t.s;
        return e < t.e;
    }
};

int n, k, q;
int arr[MAXN];
vector<Query> queries;
list<int> pos[MAXN];
int cnt[MAXN], bucket[MAXQ];
int results[MAXN];

void add(int x, int dir) {
    auto &dq = pos[arr[x]];
    if (!dq.empty()) {
        int dist = dq.back() - dq.front();
        cnt[dist]--;
        bucket[dist / SQRTN]--;
    }
    if (dir == 1) dq.push_back(x);
    else dq.push_front(x);
    int dist = dq.back() - dq.front();
    cnt[dist]++;
    bucket[dist / SQRTN]++;
}

void remove(int x, int dir) {
    auto &dq = pos[arr[x]];
    int dist = dq.back() - dq.front();
    cnt[dist]--;
    bucket[dist / SQRTN]--;
    if (dir == 1) dq.pop_back();
    else dq.pop_front();
    if (!dq.empty()) {
        dist = dq.back() - dq.front();
        cnt[dist]++;
        bucket[dist / SQRTN]++;
    }
}

int getMaxQuery() {
    for (int i = MAXQ - 1; i >= 0; i--) {
        if (bucket[i] == 0) continue;
        for (int j = SQRTN - 1; j >= 0; j--) {
            if (cnt[i * SQRTN + j] > 0) {
                return i * SQRTN + j;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
        arr[i] = (arr[i] % k + k) % k;
    }
    
    cin >> q;
    queries.resize(q);
    for (int i = 0; i < q; i++) {
        int s, e;
        cin >> s >> e;
        queries[i] = Query(s - 1, e, i);
    }
    sort(queries.begin(), queries.end());

    int s = queries[0].s, e = queries[0].e;
    for (int i = s; i <= e; i++) {
        add(i, 1);
    }
    results[queries[0].x] = getMaxQuery();

    for (int i = 1; i < q; i++) {
        int x = queries[i].x;
        while (queries[i].s < s) add(--s, 0);
        while (e < queries[i].e) add(++e, 1);
        while (s < queries[i].s) remove(s++, 0);
        while (queries[i].e < e) remove(e--, 1);
        results[x] = getMaxQuery();
    }

    for (int i = 0; i < q; i++) {
        cout << results[i] << "\n";
    }

    return 0;
}