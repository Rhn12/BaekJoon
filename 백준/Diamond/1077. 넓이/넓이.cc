#include <cstdio>

#include <utility>

#include <vector>

#include <cmath>

using namespace std;

typedef long long ll;

typedef pair<int, int> pii;

typedef pair<double, double> pdd;

#define pb push_back

#define ff first

#define ss second

int n, m;

bool now, flag;

pdd u[110], v[110], st, pre;

vector<pair<pii, pdd>> intersections;

double ans;

pair<bool, pdd> meet(int p, int q) {

    pdd x1 = u[p], x2 = u[(p + 1) % n];

    pdd y1 = v[q], y2 = v[(q + 1) % m];

    double a = x1.ff - x2.ff, b = y1.ff - y2.ff;

    double c = x1.ss - x2.ss, d = y1.ss - y2.ss;

    if (a * d == b * c) return {false, {0, 0}};

    double t = ((y1.ff - x2.ff) * d - (y1.ss - x2.ss) * b) / (a * d - b * c);

    double s = ((y1.ff - x2.ff) * c - (y1.ss - x2.ss) * a) / (b * c - a * d);

    if (t < 0 || t >= 1 || s < 0 || s >= 1) return {false, {t, s}};

    return {true, {t * x1.ff + (1 - t) * x2.ff, t * x1.ss + (1 - t) * x2.ss}};

}

double surface(pdd p, pdd q, pdd r) {

    return ((p.ff - q.ff) * (p.ss - r.ss) - (p.ss - q.ss) * (p.ff - r.ff)) * 0.5;

}

void addSurface(pdd p) {

    if (flag) ans += surface(intersections[0].ss, pre, p);

    pre = p;

    flag = true;

}

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) scanf("%lf %lf", &u[i].ff, &u[i].ss);

    for (int i = 0; i < m; i++) scanf("%lf %lf", &v[i].ff, &v[i].ss);

    for (int i = 0; i < n; i++) {

        int cnt = 0;

        for (int j = 0; j < m; j++) {

            auto tmp = meet(i, j);

            if (tmp.ff) intersections.pb({{i, j}, tmp.ss}), cnt++;

        }

        if (cnt < 2) continue;

        int j = intersections.size() - 1;

        if ((u[i].ff - intersections[j - 1].ss.ff) * (intersections[j - 1].ss.ff - intersections[j].ss.ff) +

            (u[i].ss - intersections[j - 1].ss.ss) * (intersections[j - 1].ss.ss - intersections[j].ss.ss) < 0) {

            swap(intersections[j - 1], intersections[j]);

        }

    }

    if (intersections.empty()) {

        pdd inf = {1010, 1010}, tmp;

        bool cnt = false;

        tmp = u[1]; u[1] = inf;

        for (int i = 0; i < m; i++) {

            auto t = meet(0, i);

            if (t.ff) cnt = !cnt;

        }

        u[1] = tmp;

        if (cnt) {

            for (int i = 2; i < n; i++) ans += surface(u[0], u[i - 1], u[i]);

            printf("%.9f", ans);

            return 0;

        }

        tmp = v[1]; v[1] = inf;

        for (int i = 0; i < n; i++) {

            auto t = meet(i, 0);

            if (t.ff) cnt = !cnt;

        }

        v[1] = tmp;

        if (cnt) {

            for (int i = 2; i < m; i++) ans += surface(v[0], v[i - 1], v[i]);

            printf("%.9f", ans);

            return 0;

        }

        printf("0");

        return 0;

    }

    double t = surface(u[intersections[0].ff.ff], intersections[0].ss, v[(intersections[0].ff.ss + 1) % m]);

    if (t != 0) now = t > 0;

    else {

        t = surface(v[intersections[0].ff.ss], intersections[0].ss, u[(intersections[0].ff.ff + 1) % n]);

        now = t < 0;

    }

    for (int i = 0, ii = intersections.size(); i < ii; i++) {

        if (i) addSurface(intersections[i].ss);

        for (int j = now ? intersections[i].ff.ss : intersections[i].ff.ff,

            jj = now ? intersections[(i + 1) % ii].ff.ss : intersections[(i + 1) % ii].ff.ff;

            j != jj;) {

            j++; j %= (now ? m : n);

            addSurface(now ? v[j] : u[j]);

        }

        now = !now;

    }

    printf("%.9f", ans);

    return 0;

}