#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int ALPHABET_SIZE = 4;

struct Trie {
    Trie* next[ALPHABET_SIZE];
    Trie* fail;
    int output;

    Trie() : output(0), fail(nullptr) {
        fill(next, next + ALPHABET_SIZE, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            delete next[i];
        }
    }

    void insert(const string& s, int idx) {
        if (idx >= s.length()) {
            output = 1;
            return;
        }
        int x = s[idx] - '0';
        if (!next[x]) {
            next[x] = new Trie();
        }
        next[x]->insert(s, idx + 1);
    }
};

void build_fail_links(Trie* root) {
    queue<Trie*> q;
    root->fail = root;
    q.push(root);
    while (!q.empty()) {
        Trie* cur = q.front();
        q.pop();
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            Trie* nxt = cur->next[i];
            if (!nxt)
                continue;
            if (root == cur) {
                nxt->fail = root;
            } else {
                Trie* tmp = cur->fail;
                while (tmp != root && !tmp->next[i])
                    tmp = tmp->fail;
                if (tmp->next[i])
                    tmp = tmp->next[i];
                nxt->fail = tmp;
            }
            nxt->output += nxt->fail->output;
            q.push(nxt);
        }
    }
}

int solve(const string& s, Trie* root) {
    int ret = 0;
    Trie* cur = root;
    for (char c : s) {
        int nxt = c - '0';
        while (cur != root && !cur->next[nxt])
            cur = cur->fail;
        if (cur->next[nxt])
            cur = cur->next[nxt];
        ret += cur->output;
    }
    return ret;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;
        string s, m;
        cin >> s >> m;

        for (char& c : s) {
            switch (c) {
                case 'A': c = '0'; break;
                case 'C': c = '1'; break;
                case 'G': c = '2'; break;
                case 'T': c = '3'; break;
            }
        }
        for (char& c : m) {
            switch (c) {
                case 'A': c = '0'; break;
                case 'C': c = '1'; break;
                case 'G': c = '2'; break;
                case 'T': c = '3'; break;
            }
        }

        Trie* root = new Trie();
        root->insert(m, 0);

        for (int i = 0; i <= M; i++) {
            for (int j = i + 2; j <= M; j++) {
                reverse(m.begin() + i, m.begin() + j);
                root->insert(m, 0);
                reverse(m.begin() + i, m.begin() + j);
            }
        }

        build_fail_links(root);
        cout << solve(s, root) << "\n";
        delete root;
    }
}