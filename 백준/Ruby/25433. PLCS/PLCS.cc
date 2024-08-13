#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long int

bool is_prime[50001];
vector<int> primes;

int calculate_lcs(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    int bitset_len = (len2 >> 6) + 1;
    vector<vector<ull>> bitsets(256, vector<ull>(bitset_len, 0));
    
    for (int i = 0; i < len2; i++) {
        bitsets[str2[i]][i >> 6] |= 1ULL << (i & 63);
    }
    
    vector<ull> current_row(bitset_len, 0);
    
    for (int i = 0; i < len1; i++) {
        ull carry_set = 1;
        ull carry_mid = 0;
        
        for (int n = 0; n < bitset_len; n++) {
            ull x = bitsets[str1[i]][n] | current_row[n];
            ull temp = current_row[n];
            current_row[n] = x & (x ^ (x - ((current_row[n] << 1) + carry_set) - carry_mid));
            carry_mid = (x < ((temp << 1) + carry_set) + carry_mid) ? 1 : 0;
            carry_set = temp >> 63;
        }
    }
    
    int lcs_length = 0;
    for (int n = 0; n < bitset_len; n++) {
        lcs_length += __builtin_popcountll(current_row[n]);
    }
    return lcs_length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string strA, strB;
    cin >> strA >> strB;
    char charX, charY;
    cin >> charX >> charY;

    strA.erase(remove(strA.begin(), strA.end(), charY), strA.end());
    strB.erase(remove(strB.begin(), strB.end(), charY), strB.end());

    int indexA = strA.find(charX);
    int indexB = strB.find(charX);

    int result = 1 + calculate_lcs(strA.substr(0, indexA), strB.substr(0, indexB)) + calculate_lcs(strA.substr(indexA + 1), strB.substr(indexB + 1));

    memset(is_prime, 0, sizeof(is_prime));
    primes.push_back(-1);
    for (int i = 2; i <= 50000; i++) {
        if (!is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= 50000; j += i) {
                is_prime[j] = true;
            }
        }
    }

    result = *(--upper_bound(primes.begin(), primes.end(), result));
    cout << result;
}