#include "testlib.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

static vector<int> bfsOrder(int n, const vector<vector<int>>& graph) {
    vector<int> order;
    vector<int> seen(n + 1, 0);
    queue<int> q;
    q.push(1);
    seen[1] = 1;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        order.push_back(x);

        vector<int> children;
        for (int y : graph[x]) {
            if (!seen[y]) {
                seen[y] = 1;
                children.push_back(y);
            }
        }
        shuffle(children.begin(), children.end());
        for (int y : children) q.push(y);
    }

    return order;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(5);
    vector<pair<int, int>> edges;

    for (int v = 2; v <= n; ++v) {
        int parent = 1;
        if (mode == 0) {
            parent = v - 1;
        } else if (mode == 1) {
            parent = 1;
        } else if (mode == 2) {
            parent = v / 2;
        } else if (mode == 3) {
            parent = rnd.next(1, v - 1);
        } else {
            parent = max(1, v - rnd.next(1, min(4, v - 1)));
        }
        edges.push_back({parent, v});
    }

    shuffle(edges.begin(), edges.end());
    vector<vector<int>> graph(n + 1);
    for (auto& edge : edges) {
        if (rnd.next(2)) swap(edge.first, edge.second);
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
    for (int i = 1; i <= n; ++i) shuffle(graph[i].begin(), graph[i].end());

    vector<int> order = bfsOrder(n, graph);
    if (rnd.next(2) && n >= 4) {
        for (int tries = 0; tries < 8; ++tries) {
            int a = rnd.next(1, n - 1);
            int b = rnd.next(1, n - 1);
            if (a != b) {
                swap(order[a], order[b]);
                break;
            }
        }
    }

    println(n);
    for (const auto& edge : edges) println(edge.first, edge.second);
    println(order);

    return 0;
}
