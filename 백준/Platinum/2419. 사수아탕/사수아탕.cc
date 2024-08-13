#include <stdio.h>
#include <algorithm>
#define INF 5000000
using namespace std;
int mem[2][302][302], baskl[301], baskr[301];
int n, m, cnt, re, ml, mr, in;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &in);
		if (in > 0) baskr[++mr] = in;
		else baskl[++ml] = in;
	}
	sort(baskl, baskl + ml + 1, greater<int>());
	sort(baskr, baskr + mr + 1);
	baskr[mr+1] = INF, baskl[ml+1] = -INF;
	cnt = 0;
	while (cnt < n) {
		for (int lp = min(ml, cnt); lp >= 0; lp--) {
			for (int rp = min(mr, cnt - lp); rp >= 0; rp--) {
				mem[0][lp][rp] = min(
					mem[0][lp + 1][rp] + (baskl[lp] - baskl[lp + 1]) * (cnt - lp - rp + 1),
					mem[1][lp][rp + 1] + (baskr[rp + 1] - baskl[lp]) * (cnt - lp - rp + 1)
				);
				mem[1][lp][rp] = min(
					mem[0][lp + 1][rp] + (baskr[rp] - baskl[lp + 1]) * (cnt - lp - rp + 1),
					mem[1][lp][rp + 1] + (baskr[rp + 1] - baskr[rp]) * (cnt - lp - rp + 1)
				);
			}
		}
		re = max(re, (++cnt) * m - mem[0][0][0]);
	}
	printf("%d", re);
	return 0;
}