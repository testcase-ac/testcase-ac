#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int randomWeight(int mode) {
    if (mode == 0) return rnd.next(0, 20);
    if (mode == 1) return rnd.next(499900, 500000);
    if (mode == 2) return rnd.any(vector<int>{0, 1, 10, 1000, 500000});
    return rnd.next(0, 500000);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int weightMode) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (!used.insert({u, v}).second) return;
    edges.push_back({u, v, randomWeight(weightMode)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int weightMode = rnd.next(0, 3);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(2, 14);
        for (int v = 2; v <= n; ++v) {
            if (rnd.next(0, 99) < 75) {
                addEdge(edges, used, v, rnd.next(1, v - 1), weightMode);
            }
        }
        if (edges.empty()) addEdge(edges, used, 1, 2, weightMode);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        for (int i = 1; i <= n; ++i) {
            int j = i == n ? 1 : i + 1;
            addEdge(edges, used, i, j, weightMode);
        }
        int extra = rnd.next(0, min(8, n * (n - 1) / 2 - n));
        while (extra > 0) {
            int before = int(edges.size());
            addEdge(edges, used, rnd.next(1, n), rnd.next(1, n), weightMode);
            if (int(edges.size()) > before) --extra;
        }
    } else if (mode == 2) {
        n = rnd.next(4, 11);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(n, int(candidates.size()));
        for (int i = 0; i < m; ++i) {
            addEdge(edges, used, candidates[i].first, candidates[i].second, weightMode);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 14);
        int split = rnd.next(3, n - 2);
        for (int v = 2; v <= split; ++v) {
            addEdge(edges, used, v - 1, v, weightMode);
        }
        if (split >= 3) addEdge(edges, used, 1, split, weightMode);
        for (int v = split + 2; v <= n; ++v) {
            addEdge(edges, used, v - 1, v, weightMode);
        }
        if (n - split >= 3) addEdge(edges, used, split + 1, n, weightMode);
        if (rnd.next(0, 1)) addEdge(edges, used, rnd.next(1, split), rnd.next(split + 1, n), weightMode);
    } else {
        n = rnd.any(vector<int>{100, 1000, 100000});
        int m = rnd.next(1, 8);
        vector<int> labels = {1, 2, n / 2, n - 1, n};
        while (int(labels.size()) < m + 2) labels.push_back(rnd.next(1, n));
        while (int(edges.size()) < m) {
            addEdge(edges, used, rnd.any(labels), rnd.any(labels), weightMode);
        }
    }

    shuffle(edges.begin(), edges.end());
    for (Edge& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.u, edge.v);
    }

    println(n, int(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
}
