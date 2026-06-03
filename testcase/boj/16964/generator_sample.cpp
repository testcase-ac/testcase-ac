#include "testlib.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

static vector<int> rootedParents(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    queue<int> q;
    parent[1] = -1;
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : graph[node]) {
            if (parent[next] == 0) {
                parent[next] = node;
                q.push(next);
            }
        }
    }
    return parent;
}

static bool isDfsOrder(const vector<int>& order, const vector<int>& parent) {
    if (order.empty() || order[0] != 1) return false;

    vector<int> path;
    path.push_back(1);
    for (int i = 1; i < (int)order.size(); ++i) {
        int node = order[i];
        while (!path.empty() && parent[node] != path.back()) path.pop_back();
        if (path.empty()) return false;
        path.push_back(node);
    }
    return true;
}

static vector<int> makeValidOrder(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n + 1);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) shuffle(graph[i].begin(), graph[i].end());

    vector<int> order;
    vector<int> parent(n + 1, 0);
    vector<int> stack = {1};
    parent[1] = -1;
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);

        vector<int> children;
        for (int next : graph[node]) {
            if (next != parent[node]) {
                parent[next] = node;
                children.push_back(next);
            }
        }
        reverse(children.begin(), children.end());
        for (int child : children) stack.push_back(child);
    }
    return order;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 15);
    int mode = rnd.next(5);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) edges.push_back({i - 1, i});
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) edges.push_back({1, i});
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) edges.push_back({i / 2, i});
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) edges.push_back({i - 1, i});
        for (int i = spine + 1; i <= n; ++i) edges.push_back({rnd.next(1, spine), i});
    } else {
        for (int i = 2; i <= n; ++i) edges.push_back({rnd.next(1, i - 1), i});
    }

    vector<int> order = makeValidOrder(n, edges);
    vector<int> parent = rootedParents(n, edges);
    if (rnd.next(2) == 0) {
        if (rnd.next(3) == 0) {
            swap(order[0], order[rnd.next(1, n - 1)]);
        } else {
            for (int tries = 0; tries < 100 && isDfsOrder(order, parent); ++tries) {
                shuffle(order.begin(), order.end());
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(2)) swap(edge.first, edge.second);
    }

    println(n);
    for (auto [u, v] : edges) println(u, v);
    println(order);

    return 0;
}
