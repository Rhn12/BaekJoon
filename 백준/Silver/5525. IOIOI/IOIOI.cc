#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;

    int count = 0;
    int pattern_length = 2 * N + 1;
    int i = 0;

    while (i < M - 1) {
        int match_length = 0;
        if (S[i] == 'I') {
            while (S[i + 1] == 'O' && S[i + 2] == 'I') {
                match_length++;
                if (match_length == N) {
                    count++;
                    match_length--;
                }
                i += 2;
            }
        }
        i++;
    }

    cout << count << "\n";
    return 0;
}
