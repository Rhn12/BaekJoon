#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, h = 1;
pair<int, int> c[100000];
vector<int> seg1, seg2;

void update(vector<int> &s, int idx, int v) {
	idx += h;
	s[idx] += v;
	while (idx > 1) {
		idx /= 2;
		s[idx] = s[idx * 2] + s[idx * 2 + 1];
	}
}

int query(int l, int r, int idx, int L, int R) {
	if (idx >= h) {
		(l < r ? l : r) += seg1[idx];
		(L < R ? L : R) += seg2[idx];
		return max({ l, r, L, R });
	}
	int l1 = l + seg1[idx * 2], l2 = L + seg2[idx * 2], r1 = r + seg1[idx * 2 + 1], r2 = R + seg2[idx * 2 + 1];
	return max(l1, l2) < max(r1, r2) ? query(l1, r, idx * 2 + 1, l2, R) : query(l, r1, idx * 2, L, r2);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> N;
	while (h < N) h <<= 1;
	seg1.resize(h * 2);
	seg2.resize(h * 2);
	for (int i = 0; i < N; i++) cin >> c[i].first >> c[i].second;
	sort(c, c + N);
	for (int i = 0, idx = 0, x = c[i].first; i < N; i++) {
		if (x != c[i].first) {
			x = c[i].first;
			idx++;
		}
		c[i].first = idx;
	}
	sort(c, c + N, [](pair<int, int> p1, pair<int, int> p2) {
		return p1.second < p2.second;
	});
	for (int i = 0; i < N; i++) update(seg1, c[i].first, 1);
	int ans = N;
	for (int i = 0; i < N;) {
		int j = 0;
		for (; i + j < N && c[i].second == c[i + j].second; j++) {
			update(seg1, c[i + j].first, -1);
			update(seg2, c[i + j].first, 1);
		}
		ans = min(ans, query(0, 0, 1, 0, 0));
		i += j;
	}
	cout << ans << '\n';

	return 0;
}