#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int u, int v) {
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) {
        edges.push_back({u, v});
    }
}

static void addRandomTree(int n, set<pair<int, int>>& used, vector<pair<int, int>>& edges) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());
    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(0, i - 1)];
        addEdge(used, edges, order[i], parent);
    }
}

static vector<pair<int, int>> remainingEdges(int n, const set<pair<int, int>>& used) {
    vector<pair<int, int>> rest;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) {
                rest.push_back({u, v});
            }
        }
    }
    shuffle(rest.begin(), rest.end());
    return rest;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = 2;
        addEdge(used, edges, 1, 2);
    } else if (mode == 1) {
        n = rnd.next(3, 40);
        for (int i = 1; i < n; ++i) addEdge(used, edges, i, i + 1);
    } else if (mode == 2) {
        n = rnd.next(3, 60);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) addEdge(used, edges, center, i);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 50);
        for (int i = 1; i <= n; ++i) addEdge(used, edges, i, i == n ? 1 : i + 1);
    } else if (mode == 4) {
        n = rnd.next(5, 80);
        addRandomTree(n, used, edges);
    } else if (mode == 5) {
        n = rnd.next(5, 70);
        addRandomTree(n, used, edges);
        vector<pair<int, int>> rest = remainingEdges(n, used);
        int extra = rnd.next(1, min<int>((int)rest.size(), 2 * n));
        for (int i = 0; i < extra; ++i) addEdge(used, edges, rest[i].first, rest[i].second);
    } else if (mode == 6) {
        n = rnd.next(6, 45);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 65) addEdge(used, edges, u, v);
            }
        }
        addRandomTree(n, used, edges);
    } else {
        n = rnd.next(2, 32);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) addEdge(used, edges, u, v);
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1)) swap(u, v);
        println(u, v);
    }
    return 0;
}
