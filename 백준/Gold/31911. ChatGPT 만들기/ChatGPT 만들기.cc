#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

char next_char(char c, unordered_map<char, unordered_map<char, int>>& t_map) {
    if (t_map.find(c) == t_map.end()) {
        return '\0';
    }
    auto next_chars = t_map[c];
    int max_count = 0;
    for (auto& nc : next_chars) {
        max_count = max(max_count, nc.second);
    }
    vector<char> candidates;
    for (auto& nc : next_chars) {
        if (nc.second == max_count) {
            candidates.push_back(nc.first);
        }
    }
    return *min_element(candidates.begin(), candidates.end());
}
unordered_map<char, unordered_map<char, int>> build_map(vector<string>& sentences) {
    unordered_map<char, unordered_map<char, int>> t_map;
    for (auto& s : sentences) {
        for (int i = 0; i < s.size() - 1; ++i) {
            char cur = s[i];
            char nxt = s[i + 1];
            if (t_map[cur].find(nxt) == t_map[cur].end()) {
                t_map[cur][nxt] = 0;
            }
            t_map[cur][nxt]++;
        }
    }
    return t_map;
}
string gen_string(unordered_map<char, unordered_map<char, int>>& t_map, char start, int length) {
    string res = "";
    char cur = start;
    res += start;
    for (int i = 0; i < length - 1; ++i) {
        char nxt = next_char(cur, t_map);
        if (nxt == '\0') {
            break;
        }
        res += nxt;
        cur = nxt;
    }
    return res;
}
string solve(int n, int k, int m, vector<string>& sentences) {
    auto t_map = build_map(sentences);
    string gen_str = gen_string(t_map, '[', k + m - 1);
    if (gen_str.size() < k + m - 1) {
        gen_str += string(k + m - 1 - gen_str.size(), '.');
    }
    string result = gen_str.substr(k - 1, m);
    if (result.size() < m) {
        result += string(m - result.size(), '.');
    }
    return result;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, m;
    cin >> n >> k >> m;
    vector<string> sentences(n);
    for (int i = 0; i < n; ++i) {
        cin >> sentences[i];
    }
    string result = solve(n, k, m, sentences);
    cout << result << endl;
    return 0;
}