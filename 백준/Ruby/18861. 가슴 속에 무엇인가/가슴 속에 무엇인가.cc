#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    Node *left, *right, *parent, *minNode;
    bool flipFlag;
    int value;
    
    Node(int v = 0) : left(nullptr), right(nullptr), parent(nullptr), flipFlag(false), minNode(this), value(v) {}
};

const int MAX_N = 1101010;
Node tree[MAX_N];
priority_queue<pair<int, Node*>> primaryQueue, secondaryQueue;
int nodeCount, totalNodes;

Node* newNode() {
    return &tree[nodeCount++];
}

bool isLeftChild(Node* node) {
    return node == node->parent->left;
}

bool isRoot(Node* node) {
    return !node->parent || (node != node->parent->left && node != node->parent->right);
}

void flip(Node* node) {
    node->flipFlag ^= 1;
    swap(node->left, node->right);
}

void update(Node* node) {
    node->minNode = node;
    if (node->left && node->minNode->value > node->left->minNode->value) {
        node->minNode = node->left->minNode;
    }
    if (node->right && node->minNode->value > node->right->minNode->value) {
        node->minNode = node->right->minNode;
    }
}

void pushDown(Node* node) {
    if (node->flipFlag) {
        if (node->left) flip(node->left);
        if (node->right) flip(node->right);
        node->flipFlag = false;
    }
}

void rotate(Node* node) {
    Node* parent = node->parent;
    pushDown(parent); pushDown(node);
    if (isLeftChild(node)) {
        if (node->right) node->right->parent = parent;
        parent->left = node->right; node->right = parent;
    } else {
        if (node->left) node->left->parent = parent;
        parent->right = node->left; node->left = parent;
    }
    if (!isRoot(parent)) {
        if (isLeftChild(parent)) parent->parent->left = node;
        else parent->parent->right = node;
    }
    node->parent = parent->parent; parent->parent = node; update(parent); update(node);
}

void splay(Node* node) {
    while (!isRoot(node)) {
        if (!isRoot(node->parent)) {
            if (isLeftChild(node) ^ isLeftChild(node->parent)) rotate(node);
            else rotate(node->parent);
        }
        rotate(node);
    }
}

void access(Node* node) {
    splay(node); pushDown(node);
    node->right = nullptr; update(node);
    while (node->parent) {
        splay(node->parent); pushDown(node->parent);
        node->parent->right = node; update(node->parent);
        splay(node);
    }
}

void makeRoot(Node* node) {
    access(node); flip(node);
}

void link(Node* u, Node* v) {
    access(u); access(v);
    u->left = v; v->parent = u; update(u);
}

void cut(Node* node) {
    access(node);
    if (node->left) {
        node->left->parent = nullptr;
        node->left = nullptr;
        update(node);
    }
}

void addEdge(Node* u, Node* v, int cost) {
    access(u); access(v); splay(u);
    Node* minU = (u->parent) ? u->minNode : u;
    access(u); splay(v);
    Node* minV = (v->parent) ? v->minNode : v;

    if (u->parent || v->parent) {
        if (minU->value > minV->value) swap(u, v), swap(minU, minV);
        if (minU->value >= cost) return;
        cut(minU); makeRoot(u); cut(minU);
        secondaryQueue.emplace(-minU->value, minU);
        *minU = Node(cost); link(u, minU); link(minU, v);
        primaryQueue.emplace(-minU->value, minU);
    } else {
        Node* newNode = new Node(cost);
        makeRoot(u); link(u, newNode); link(newNode, v);
        primaryQueue.emplace(-newNode->value, newNode);
    }
}

int query(Node* u, Node* v) {
    access(u); access(v); splay(u);
    Node* minU = (u->parent) ? u->minNode : u;
    access(u); splay(v);
    Node* minV = (v->parent) ? v->minNode : v;

    if (u->parent || v->parent) {
        return min(minU->value, minV->value);
    } else {
        return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int q, type, u, v, cost;
    cin >> nodeCount >> q;
    
    for (int i = 1; i <= nodeCount; ++i) {
        tree[i] = Node(2e9);
    }
    totalNodes = nodeCount + 1;

    while (q--) {
        cin >> type;
        if (type == 1) {
            cin >> u >> v >> cost;
            addEdge(&tree[u], &tree[v], cost);
        } else if (type == 2) {
            cin >> cost;
            while (!primaryQueue.empty() && -primaryQueue.top().first < cost) {
                if (secondaryQueue.empty() || primaryQueue.top() != secondaryQueue.top()) {
                    cut(primaryQueue.top().second);
                } else {
                    secondaryQueue.pop();
                }
                primaryQueue.pop();
            }
        } else if (type == 3) {
            cin >> u >> v;
            cout << query(&tree[u], &tree[v]) << "\n";
        }
    }

    return 0;
}