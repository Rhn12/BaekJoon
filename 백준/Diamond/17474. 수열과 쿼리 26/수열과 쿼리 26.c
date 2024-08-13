#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef long long ll;
const int INF = 10000000000;
typedef struct {
    int max1, max2, cnt_max;
    ll sum;
} NODE;
typedef struct {
    int n;
    NODE *tree;
} SEG_TREE;
NODE add(NODE a, NODE b) {
    if (a.max1 == b.max1) 
        return (NODE){a.max1, (a.max2 > b.max2) ? a.max2 : b.max2, a.cnt_max + b.cnt_max, a.sum + b.sum};
    else if (a.max1 > b.max1) 
        return (NODE){a.max1, (a.max2 > b.max1) ? a.max2 : b.max1, a.cnt_max, a.sum + b.sum};
    else 
        return (NODE){b.max1, (a.max1 > b.max2) ? a.max1 : b.max2, b.cnt_max, a.sum + b.sum};
}
NODE init(NODE *tree, int *v, int left, int right, int node) {
    if (left == right) 
        return tree[node] = (NODE){v[left], -INF, 1, v[left]};
    int mid = (left + right) / 2;
    return tree[node] = add(init(tree, v, left, mid, node * 2), init(tree, v, mid + 1, right, node * 2 + 1));
}
void lazy_propagation(NODE *tree, int left, int right, int node) {
    if (left != right) {
        for (int idx = node * 2; idx <= node * 2 + 1; idx++) {
            if (tree[node].max1 < tree[idx].max1) {
                tree[idx].sum -= (ll)tree[idx].cnt_max * (tree[idx].max1 - tree[node].max1);
                tree[idx].max1 = tree[node].max1;
            }
        }
    }
}
void update(NODE *tree, int left, int right, int k, int nodeLeft, int nodeRight, int node) {
    lazy_propagation(tree, nodeLeft, nodeRight, node);
    if (nodeRight < left || right < nodeLeft || tree[node].max1 <= k) 
        return;
    if (left <= nodeLeft && nodeRight <= right && tree[node].max2 < k) {
        tree[node].sum -= (ll)tree[node].cnt_max * (tree[node].max1 - k);
        tree[node].max1 = k;
        lazy_propagation(tree, nodeLeft, nodeRight, node);
        return;
    }
    int mid = (nodeLeft + nodeRight) / 2;
    update(tree, left, right, k, nodeLeft, mid, node * 2);
    update(tree, left, right, k, mid + 1, nodeRight, node * 2 + 1);
    tree[node] = add(tree[node * 2], tree[node * 2 + 1]);
}
int query_max(NODE *tree, int left, int right, int nodeLeft, int nodeRight, int node) {
    lazy_propagation(tree, nodeLeft, nodeRight, node);
    if (nodeRight < left || right < nodeLeft) 
        return -INF;
    if (left <= nodeLeft && nodeRight <= right) 
        return tree[node].max1;
    int mid = (nodeLeft + nodeRight) / 2;
    int left_max = query_max(tree, left, right, nodeLeft, mid, node * 2);
    int right_max = query_max(tree, left, right, mid + 1, nodeRight, node * 2 + 1);
    return (left_max > right_max) ? left_max : right_max;
}
ll query_sum(NODE *tree, int left, int right, int nodeLeft, int nodeRight, int node) {
    lazy_propagation(tree, nodeLeft, nodeRight, node);
    if (nodeRight < left || right < nodeLeft) 
        return 0;
    if (left <= nodeLeft && nodeRight <= right) 
        return tree[node].sum;
    int mid = (nodeLeft + nodeRight) / 2;
    return query_sum(tree, left, right, nodeLeft, mid, node * 2) + query_sum(tree, left, right, mid + 1, nodeRight, node * 2 + 1);
}
int main() {
    int N, Q;
    scanf("%d", &N);
    int *v = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }
    SEG_TREE seg;
    seg.n = N;
    seg.tree = (NODE *)malloc(N * 4 * sizeof(NODE));
    init(seg.tree, v, 0, N - 1, 1);
    scanf("%d", &Q);
    while (Q--) {
        int type, left, right, x;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &left, &right, &x);
            update(seg.tree, left - 1, right - 1, x, 0, N - 1, 1);
        } else if (type == 2) {
            scanf("%d %d", &left, &right);
            printf("%d\n", query_max(seg.tree, left - 1, right - 1, 0, N - 1, 1));
        } else if (type == 3) {
            scanf("%d %d", &left, &right);
            printf("%lld\n", query_sum(seg.tree, left - 1, right - 1, 0, N - 1, 1));
        }
    }
    free(v);
    free(seg.tree);
    return 0;
}