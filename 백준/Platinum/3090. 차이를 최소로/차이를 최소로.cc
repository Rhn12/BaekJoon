#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const int MAX_N = 1e5 + 2;

LL oprCnt;
int N, T;
int arr[MAX_N], copyArr[MAX_N];

bool isPossible(int mid) {
    oprCnt = 0;
    for (int i = 0; i < N; i++)
        copyArr[i] = arr[i];

    for (int i = 0; i < N - 1; i++) {
        if (copyArr[i + 1] - copyArr[i] > mid) {
            oprCnt += copyArr[i + 1] - (copyArr[i] + mid);
            copyArr[i + 1] = copyArr[i] + mid;
        }
    }

    for (int i = N - 1; i > 0; i--) {
        if (copyArr[i - 1] - copyArr[i] > mid) {
            oprCnt += copyArr[i - 1] - (copyArr[i] + mid);
            copyArr[i - 1] = copyArr[i] + mid;
        }
    }
    return oprCnt <= T ? true : false;
}

void printAnsArr(int mid) {
    for (int i = 0; i < N - 1; i++)
        if (arr[i + 1] - arr[i] > mid)
            arr[i + 1] = arr[i] + mid;

    for (int i = N - 1; i > 0; i--)
        if (arr[i - 1] - arr[i] > mid)
            arr[i - 1] = arr[i] + mid;

    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> T;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int left = 0, right = 1e9;
    while (left < right) {
        int mid = (left + right) / 2;
        if (isPossible(mid))
            right = mid;
        else
            left = mid + 1;
    }
    printAnsArr(right);
}