#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
constexpr int INF = 1e9 + 7;
int n, m, v[9][9];
unordered_map<string, int> cache[9][9];
string Norm(const string& s) {
    char check[10] = {};
    for (char c : s) {
        if (c != '0' && !check[c & 15]) {
            check[c & 15] = (check[0] + 1) | 48;
            check[0]++;
        }
    }
    string ret(s.size(), '0');
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0') {
            ret[i] = check[s[i] & 15];
        }
    }
    return ret;
}
string Merge(const string& s) {
    string ret = s.substr(1);
    if (s[0] == '0' && s.back() == '0') ret.push_back('9');
    else if (s[0] == '0') ret.push_back(s.back());
    else if (s.back() == '0' || s[0] == s.back()) ret.push_back(s[0]);
    else {
        ret.push_back(s[0]);
        for (char& c : ret) if (c == s.back()) c = s[0];
    }
    return Norm(ret);
}
string Merge2(const string& s) {
    string ret = s.substr(1);
    if (s[0] == '0') ret.push_back('9');
    else ret.push_back(s[0]);
    return Norm(ret);
}
bool CheckPass(const string& s) {
    if (s[0] == '0') return true;
    for (int i = 1; i < s.size(); i++) if (s[i] == s[0]) return true;
    return false;
}
bool CheckValid(const string& s) {
    char check[10] = {};
    for (char c : s) check[c & 15] = 1;
    int cnt = 0;
    for (int i = 1; i < 10; i++) if (check[i]) cnt++;
    return cnt <= 1;
}
int DFS(int x, int y, string cur) {
    if (x == n) return CheckValid(cur) ? 0 : INF;
    cur = Norm(cur);
    if (cache[x][y].count(cur)) return cache[x][y][cur];

    int& ret = cache[x][y][cur] = INF;
    int nx = x, ny = y + 1;
    if (ny >= m) nx++, ny = 0;

    if (CheckPass(cur)) {
        string nxt = cur.substr(1) + '0';
        ret = min(ret, DFS(nx, ny, nxt));
    }
    ret = min(ret, DFS(nx, ny, y ? Merge(cur) : Merge2(cur)) + v[x][y]);
    if (CheckValid(cur)) ret = min(ret, 0);
    return ret;
}
int main() {
    fastio;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    cout << DFS(0, 0, string(m, '0')) << '\n';
}