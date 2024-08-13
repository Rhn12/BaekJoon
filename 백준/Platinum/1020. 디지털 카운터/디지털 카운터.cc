#include <cstdio>
#include <cstring>

using namespace std;

int digits[15], length, segments[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
char dp[16][106][2];
long long start = 0, end = 0;

char calculateSegments(int pos, int remainingSegments, bool isTight) {
    char &ret = dp[pos][remainingSegments][isTight];
    if (ret != -1) return ret;
    if (pos == length) return ret = (!remainingSegments && !isTight);

    ret = 0;
    for (int i = (isTight ? digits[pos] : 0); i < 10; i++) {
        if (remainingSegments >= segments[i]) {
            ret |= calculateSegments(pos + 1, remainingSegments - segments[i], (isTight && i == digits[pos]));
        }
    }
    return ret;
}

void constructNumber(int pos, int remainingSegments, bool isTight) {
    if (pos == length) return;

    for (int i = (isTight ? digits[pos] : 0); i < 10; i++) {
        if (remainingSegments >= segments[i] && calculateSegments(pos + 1, remainingSegments - segments[i], (isTight && i == digits[pos]))) {
            end = end * 10 + i;
            constructNumber(pos + 1, remainingSegments - segments[i], (isTight && i == digits[pos]));
            return;
        }
    }
}

int main() {
    int totalSegments = 0;
    long long powerOf10 = 1;
    
    while (scanf("%1d", digits + length) > 0) {
        totalSegments += segments[digits[length]];
        start = start * 10 + digits[length];
        powerOf10 *= 10;
        length++;
    }

    memset(dp, -1, sizeof(dp));
    
    if (calculateSegments(0, totalSegments, true)) {
        constructNumber(0, totalSegments, true);
        printf("%lld", end - start);
    } else {
        constructNumber(0, totalSegments, false);
        printf("%lld", powerOf10 - start + end);
    }

    return 0;
}