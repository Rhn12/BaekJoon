#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

struct Line {
    ll slope, intercept;
    Line() : slope(0), intercept(0) {}
    Line(ll slope_, ll intercept_) : slope(slope_), intercept(intercept_) {}
    ll value_at(ll x) { return slope * x + intercept; }
};

vector<Line> lines;
int line_count = 1;
vector<ll> dp, values, penalties;
vector<vector<pair<int, ll>>> graph;
int num_nodes;

ld intersection(Line &line1, Line &line2) {
    return (ld)(line1.intercept - line2.intercept) / (line2.slope - line1.slope);
}

int add_new_line(Line &new_line) {
    int low = 1, high = line_count;
    while (low < high) {
        int mid = (low + high) >> 1;
        if (intersection(lines[mid - 1], new_line) < intersection(lines[mid], lines[mid - 1]))
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

ll query_value(ll x) {
    int low = 0, high = line_count - 1;
    while (low < high) {
        int mid = (low + high + 1) >> 1;
        if (intersection(lines[mid], lines[mid - 1]) < x)
            low = mid;
        else
            high = mid - 1;
    }
    return lines[low].value_at(x);
}

void depth_first_search(int current, int parent, ll distance) {
    int rollback_index, rollback_count = line_count;
    Line rollback_line;
    if (parent) {
        dp[current] = query_value(values[current]) + distance * values[current] + penalties[current];
        Line current_line(-distance, dp[current]);
        rollback_index = add_new_line(current_line);
        rollback_line = lines[rollback_index];
        lines[rollback_index] = current_line;
        line_count = rollback_index + 1;
    }
    for (auto &neighbor : graph[current]) {
        int next_node = neighbor.first;
        ll weight = neighbor.second;
        if (next_node == parent) continue;
        depth_first_search(next_node, current, distance + weight);
    }
    if (parent) {
        lines[rollback_index] = rollback_line;
        line_count = rollback_count;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> num_nodes;
    dp.resize(num_nodes + 1);
    penalties.resize(num_nodes + 1);
    values.resize(num_nodes + 1);
    graph.resize(num_nodes + 1);
    lines.resize(num_nodes + 1, Line());

    for (int i = 1; i < num_nodes; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    for (int i = 2; i <= num_nodes; ++i) {
        cin >> penalties[i] >> values[i];
    }
    
    depth_first_search(1, 0, 0);
    
    for (int i = 2; i <= num_nodes; ++i) {
        cout << dp[i] << " \n"[i == num_nodes];
    }

    return 0;
}