#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 500001;

int tree[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
int n;

void Update(int x, int val) {
	while (x <= n) {
		tree[x] = min(tree[x], val);
		x += x & -x;
	}
}

int Query(int x) {
	int cnt = 10000000;
	while (x > 0) {
		cnt = min(cnt, tree[x]);
		x -= x & -x;
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); 
	cout.tie(0);
	cin >> n;

	for (int i = 1; i <= n; i++) tree[i] = 10000000;

	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		b[x] = i;
	}
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		c[x] = i;
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		int y = Query(b[x] - 1);
		if (c[x] < y) ans += 1;
		Update(b[x], c[x]);
	}

	cout << ans << '\n';
	return 0;
}