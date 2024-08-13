#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long N, result = 0;
    vector<int> v(6); // 주사위의 각 면의 값
    int one = 5000, two = 5000, three = 5000; // 1면, 2면, 3면 최소 조합
    int largest = 0, sum = 0; // 가장 큰 눈과 눈의 합

    cin >> N;

    for (int i = 0; i < 6; i++) {
        cin >> v[i];
        sum += v[i];
        largest = max(largest, v[i]);
    }
    for (int i = 0; i < 6; i++) {
        one = min(one, v[i]);
        for (int j = i + 1; j < 6; j++) {
            if (i + j == 5) continue;
            two = min(two, v[i] + v[j]);
            for (int k = j + 1; k < 6; k++) {
                if (i + k == 5 || j + k == 5) continue;
                three = min(three, v[i] + v[j] + v[k]);
            }
        }
    }
    if (N == 1) {
        result = sum - largest;
    } else {
        long long three_faces = 4 * three;
        long long two_faces = (8 * N - 12) * two;
        long long one_faces = (5 * N - 6) * (N - 2) * one;
        result = three_faces + two_faces + one_faces;
    }

    cout << result << endl;

    return 0;
}