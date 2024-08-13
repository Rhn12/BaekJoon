#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> tree[400002];
vector<int> lPnt[200002], rPnt[200002];

void init(int i, int l, int r, int *A){
    if(l == r){
        tree[i].push_back(A[l]);
        return;
    }
    int m = (l + r) >> 1;
    init(i * 2, l, m, A);
    init(i * 2 + 1, m + 1, r, A);
    tree[i].resize(r - l + 1);
    lPnt[i].resize(r - l + 1);
    rPnt[i].resize(r - l + 1);
    merge(tree[i * 2].begin(), tree[i * 2].end(), tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
    for(int x = 0, y = -1, z = -1; x < r - l + 1; x++){
        if(y < m - l && tree[i * 2][y + 1] == tree[i][x]) y++;
        if(z < r - m - 1 && tree[i * 2 + 1][z + 1] == tree[i][x]) z++;
        lPnt[i][x] = y, rPnt[i][x] = z;
    }
}

int query(int i, int l, int r, int s, int e, int x){
    if(l == r) return l;
    int m = (l + r) >> 1;
    int tmp = lPnt[i][e] - (s == 0 ? -1 : lPnt[i][s - 1]);
    if(x <= tmp) return query(i * 2, l, m, (s == 0 ? -1 : lPnt[i][s - 1]) + 1, lPnt[i][e], x);
    else return query(i * 2 + 1, m + 1, r, (s == 0 ? -1 : rPnt[i][s - 1]) + 1, rPnt[i][e], x - tmp);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    int arr[100002], idx[100002], loc[100002];
    for(int i = 0; i < n; i++) cin >> arr[i];

    vector<pair<int, int>> vec;
    for(int i = 0; i < n; i++) vec.push_back({arr[i], i});
    sort(vec.begin(), vec.end());
    for(int i = 0; i < n; i++) idx[vec[i].second] = i;
    for(int i = 0; i < n; i++) loc[idx[i]] = i;
    init(1, 0, n - 1, loc);

    while(q--){
        int l, r, x;
        cin >> l >> r >> x;
        int ret = query(1, 0, n - 1, l - 1, r - 1, x);
        cout << vec[ret].first << '\n';
    }
    return 0;
}