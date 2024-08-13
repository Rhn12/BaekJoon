#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

vector<int> min_factor(1025);

void setup() {
    for (int i = 2; i < 1025; i++)
        if (!min_factor[i])
            for (int j = i + i; j < 1025; j += i)
                if (!min_factor[j]) min_factor[j] = i;
}

ull powmod(ull a, ull r, ull n) {
    ull x = 1;
    while (r > 0) {
        if (r & 1) x = (__int128)a * x % n;
        a = (__int128)a * a % n;
        r >>= 1;
    }
    return x;
}

bool is_prime(ull n) {
    if (n < 1025) return n > 1 && min_factor[n] == 0;
    for (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (powmod(i, n - 1, n) != 1) return false;
    return n > 1;
}

ull gcd(ull a, ull b) {
    return b ? gcd(b, a % b) : a;
}

ull g0(ull n, ull a, ull& x, ull& y, ull& z, ull P) {
    if (is_prime(n)) return n;

    ull t, g;
    ull k = 1, l = 1;
    for (;;) {
        do {
            x = (__int128)x * x % n;
            x = (x + a) % n;
            t = (z - x + n) % n;
            P = (__int128)P * t % n;
            if (k % 32 == 1 && gcd(P, n) != 1) return gcd(P, n);
            y = x;
        } while (--k != 0);
        z = x;
        k = l;
        l = 2 * l;
        for (int i = k; i--;) {
            x = (__int128)x * x % n;
            x = (x + a) % n;
        }
        y = x;
    }
}

map<ull, int> factors;

ull g1(ull n, int a) {
    if (n < 1025) {
        for (int t; (t = min_factor[n]) && n > 1; n /= t) factors[t]++;
        return n > 1 ? (++factors[n], 1) : 1;
    }

    ull P = 1 % n;
    ull x = (P + P) % n;
    ull y = x, z = x;

    while (n > 1) {
        auto&& ff = g0(n, a, x, y, z, P);
        if (ff < 2) break;
        else if (is_prime(ff)) ++factors[ff];
        else if (ff == n || g1(ff, a + 1) == ff) break;
        n /= ff;
    }

    return n;
}

void g(ull n) {
    for (int i = 4; (n = g1(n, i)) > 1; i++);
}

int main() {
    setup();
    ull n;
    scanf("%llu", &n);
    g(n);
    ull ans = 1;
    for (auto& [i, c] : factors) {
        ull f = 1;
        while (c--) f *= i;
        ans *= f - f / i;
    }
    printf("%llu\n", ans);
    return 0;
}