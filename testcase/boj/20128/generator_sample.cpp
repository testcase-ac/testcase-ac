#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int randomWeight(int parity, bool large) {
    int lo = large ? 900000000 : 1;
    int hi = large ? 1000000000 : 40;
    int w = rnd.next(lo, hi);
    if (parity != -1 && w % 2 != parity) {
        if (w < hi) {
            ++w;
        } else {
            --w;
        }
    }
    return w;
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
             int parity, bool large) {
    if (u > v) {
        swap(u, v);
    }
    if (u == v || used.count({u, v})) {
        return;
    }
    used.insert({u, v});
    edges.push_back({u, v, randomWeight(parity, large)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 14 : 10);
    bool largeWeights = rnd.next(0, 9) == 0;

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int parity = rnd.next(0, 1);
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, v - 1, v, parity, largeWeights);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, 1, v, v % 2, largeWeights);
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, v - 1, v, -1, largeWeights);
        }
        if (n >= 3) {
            addEdge(edges, used, 1, n, rnd.next(0, 1), largeWeights);
        }
    } else {
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            addEdge(edges, used, parent, v, -1, largeWeights);
        }

        int maxEdges = static_cast<int>(candidates.size());
        int target = mode == 3 ? rnd.next(n - 1, maxEdges)
                               : min(maxEdges, n - 1 + rnd.next(1, n));
        for (auto [u, v] : candidates) {
            if (static_cast<int>(edges.size()) >= target) {
                break;
            }
            int parity = mode == 4 ? rnd.next(0, 1) : -1;
            addEdge(edges, used, u, v, parity, largeWeights);
        }
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (Edge e : edges) {
        int u = labels[e.u - 1];
        int v = labels[e.v - 1];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v, e.w);
    }

    return 0;
}
