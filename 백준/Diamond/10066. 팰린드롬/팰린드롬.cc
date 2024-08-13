#include <iostream>
#include <string>
using namespace std;
const int MAX_N = 303030;
const int MAX_ALPHA = 26;
int n;
string s;
int go[MAX_ALPHA][MAX_N], slink[MAX_N], length[MAX_N], count[MAX_N];
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> s;
    n = s.size();
    slink[1] = 0;
    length[0] = -1;
    int state = 0;
    int size = 1;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j < MAX_ALPHA; j++) { 
            go[j][i] = 1;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        while (state != 0 && (i == length[state] || s[i - length[state] - 1] != s[i]))
            state = slink[state];
        if (go[c][state] == 1) {
            length[++size] = length[state] + 2;
            int v = slink[state];
            while (v != 0 && (i == length[v] || s[i - length[v] - 1] != s[i])) {
                v = slink[v];
            }
            slink[size] = go[c][v];
            go[c][state] = size;
        }
        state = go[c][state];
        count[state]++;
    }
    for (int i = size; i > 1; i--) count[slink[i]] += count[i];
    long long answer = 0;
    for (int i = 2; i <= size; i++) {
        answer = max(answer, (long long)count[i] * length[i]);
    }
    cout << answer;
    return 0;

}