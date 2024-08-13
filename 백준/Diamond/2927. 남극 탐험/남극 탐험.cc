#include <iostream>

#include <vector>

#include <string>

using namespace std;

struct QRY {

    short a, b;

    char q, ans;

} qry[300000];

struct INFO {

    vector<short> child;

    short udx, pdx, ntx, etx;

} info[30001];

int bit[30001];

short pcnt[30001], uninfo[30001];

int N, Q;

void addt(int idx, int v) {

    while (idx <= N) {

        bit[idx] += v;

        idx += idx & -idx;

    }

}

int sumt(int idx) {

    int re = 0;

    while (idx) {

        re += bit[idx];

        idx -= idx & -idx;

    }

    return re;

}

int chunion(int n) {

    if (n == uninfo[n]) return n;

    return uninfo[n] = chunion(uninfo[n]);

}

int getsize(int ridx, int pidx = 0) {

    auto& now = info[ridx];

    int sum = 1, mx = 0;

    for (auto& nidx : now.child) {

        if (nidx == pidx) continue;

        int temp = getsize(nidx, ridx);

        sum += temp;

        if (temp > mx) mx = temp, swap(now.child.front(), nidx);

    }

    return sum;

}

void buildHLD(int ridx, int fidx = 0, int pidx = 0) {

    static int tsz = 1, chainx;

    auto& now = info[ridx];

    if (ridx != fidx) chainx = ridx, now.udx = pidx;

    addt(now.ntx = tsz++, pcnt[ridx]), now.pdx = chainx;

    for (auto& nidx : now.child) if (nidx != pidx) buildHLD(nidx, now.child.front(), ridx);

    if (ridx != fidx) now.etx = tsz;

}

int calcpenguin(int a, int b) {

    const int actx = info[a].ntx, bctx = info[b].ntx;

    int re = 0, aotx = actx, botx = bctx;

    auto* aptx = &info[info[a].pdx], * bptx = &info[info[b].pdx];

    while (!(aptx->ntx <= bctx && bctx < aptx->etx)) {

        re += sumt(aotx) - sumt(aptx->ntx - 1);

        aotx = (aptx = &info[aptx->udx])->ntx;

        aptx = &info[aptx->pdx];

    }

    while (!(bptx->ntx <= actx && actx < bptx->etx)) {

        re += sumt(botx) - sumt(bptx->ntx - 1);

        botx = (bptx = &info[bptx->udx])->ntx;

        bptx = &info[bptx->pdx];

    }

    return re += sumt(max(aotx, botx)) - sumt(min(aotx, botx) - 1);

}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    cout.tie(nullptr);

    cin >> N;

    for (int i = 1; i <= N; ++i) {

        cin >> pcnt[i];

        uninfo[i] = i;

    }

    cin >> Q;

    for (int i = 0; i < Q; ++i) {

        auto& now = qry[i];

        string in;

        cin >> in >> now.a >> now.b;

        switch (now.q = in[0]) {

        case 'e':

            now.ans = (chunion(now.a) == chunion(now.b));

            continue;

        case 'b':

            if (chunion(now.a) == chunion(now.b)) continue;

            uninfo[chunion(now.b)] = now.a;

            now.ans = 1;

            info[now.a].child.push_back(now.b);

            info[now.b].child.push_back(now.a);

        }

    }

    for (int i = 1; i <= N; ++i) {

        if (uninfo[i] == i) {

            getsize(i);

            buildHLD(i);

        }

    }

    for (int i = 0; i < Q; ++i) {

        const auto& nqry = qry[i];

        switch (nqry.q) {

        case 'b':

            cout << (nqry.ans ? "yes\n" : "no\n");

            continue;

        case 'p':

            addt(info[nqry.a].ntx, nqry.b - pcnt[nqry.a]);

            pcnt[nqry.a] = nqry.b;

            continue;

        default:

            if (!nqry.ans) {

                cout << "impossible\n";

                continue;

            }

            cout << calcpenguin(nqry.a, nqry.b) << '\n';

        }

    }

    return 0;

}