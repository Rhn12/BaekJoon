#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

string str_a, str_b, result;

void computeLCS(int start1, int end1, int start2, int end2) {
    if (start1 > end1) return;
    if (start1 == end1) {
        for (int i = start2; i <= end2; i++) {
            if (str_b[i] == str_a[start1]) {
                result.push_back(str_b[i]);
                break;
            }
        }
        return;
    }

    int mid = (start1 + end1) / 2;
    vector<int> LCS1(end2 - start2 + 3), LCS2(end2 - start2 + 3), prev(end2 - start2 + 3);

    for (int i = start1; i <= mid; i++) {
        for (int j = start2; j <= end2; j++) {
            if (str_a[i] == str_b[j]) LCS1[j - start2 + 1] = prev[j - start2] + 1;
            else LCS1[j - start2 + 1] = max(LCS1[j - start2], prev[j - start2 + 1]);
        }
        prev = LCS1;
    }

    fill(prev.begin(), prev.end(), 0);

    for (int i = end1; i > mid; i--) {
        for (int j = end2; j >= start2; j--) {
            if (str_a[i] == str_b[j]) LCS2[j - start2 + 1] = prev[j - start2 + 2] + 1;
            else LCS2[j - start2 + 1] = max(LCS2[j - start2 + 2], prev[j - start2 + 1]);
        }
        prev = LCS2;
    }

    int max_value = -1, index = 0;
    for (int i = start2; i <= end2 + 1; i++) {
        if (max_value < LCS1[i - start2] + LCS2[i - start2 + 1]) {
            max_value = LCS1[i - start2] + LCS2[i - start2 + 1];
            index = i;
        }
    }

    computeLCS(start1, mid, start2, index - 1);
    computeLCS(mid + 1, end1, index, end2);
}

int main() {
    fastio;
    cin >> str_a >> str_b;
    computeLCS(0, str_a.size() - 1, 0, str_b.size() - 1);
    cout << result.size() << '\n' << result << '\n';
}