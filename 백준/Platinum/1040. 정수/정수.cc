#include <iostream>
#include <string>

using namespace std;

const int MAX_DIGITS = 19;
const int MAX_CACHE_SIZE = 1 << 11;

int digits[MAX_DIGITS], len, K;
long long N;
string cache[MAX_CACHE_SIZE][MAX_DIGITS][2];

void calDigit() {
    long long num = N;
    while (num > 0) {
        digits[len++] = num % 10;
        num /= 10;
    }
    for (int s = 0, e = len - 1; s < e; s++, e--) {
        int tmp = digits[s];
        digits[s] = digits[e];
        digits[e] = tmp;
    }
}

string ans(int idx, int taken, int takenCnt, int pass) {
    if (idx == len)
        return takenCnt == K ? "" : "111111111111111111111111111111111";

    string& ret = cache[taken][idx][pass];
    if (!(ret.empty()))
        return ret;

    for (int d = (pass == 1 ? 0 + (idx == 0) : digits[idx]); d < 10 + (idx == 0); d++) {
        int newPass = pass || d > digits[idx];

        if (d == 10) {
            len += 1;
            ret = '1' + ans(idx + 1, taken | (1 << 1), takenCnt + !(taken & (1 << 1)), 1);
        } else
            ret = char(d + '0') + ans(idx + 1, taken | (1 << d), takenCnt + !(taken & (1 << d)), newPass);

        if (ret.size() < 30)
            return ret;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int p = 0;
    cin >> N >> K;

    calDigit();

    if (len < K) {
        len = K;
        p = 1;
    }

    cout << ans(0, 0, 0, p) << '\n';

    return 0;
}