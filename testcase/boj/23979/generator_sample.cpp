#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int c;
};

pair<int, int> randomDistinctPair(int n) {
    int u = rnd.next(1, n);
    int v = rnd.next(1, n - 1);
    if (v >= u) {
        ++v;
    }
    return {u, v};
}

int randomCost(set<int>& used) {
    int c;
    do {
        c = rnd.next(1, 200000);
    } while (used.count(c));
    used.insert(c);
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, mode == 2 ? 14 : 12);
    int q = rnd.next(2, 16);

    vector<pair<int, int>> shape;
    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            shape.push_back({v - 1, v});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                shape.push_back({center, v});
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            shape.push_back({v - 1, v});
        }
        for (int v = spine + 1; v <= n; ++v) {
            shape.push_back({rnd.next(1, spine), v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int bias = rnd.next(0, 2);
            int recent = v - rnd.next(1, min(3, v - 1));
            int parent = bias == 0 ? rnd.next(1, v - 1) : max(1, recent);
            shape.push_back({parent, v});
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    if (rnd.next(0, 1)) {
        shuffle(labels.begin(), labels.end());
    }

    vector<Edge> edges;
    set<int> usedCosts;
    for (auto [u, v] : shape) {
        edges.push_back({labels[u - 1], labels[v - 1], randomCost(usedCosts)});
    }
    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.u, edge.v);
        }
    }

    println(n, q);
    for (const auto& edge : edges) {
        println(edge.u, edge.v, edge.c);
    }

    for (int i = 0; i < q; ++i) {
        auto [u, v] = randomDistinctPair(n);
        int w = rnd.next(1, 200000);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);

        if (rnd.next(0, 2) == 0) {
            const Edge& edge = rnd.any(edges);
            u = edge.u;
            v = edge.v;
            if (rnd.next(0, 1)) {
                swap(u, v);
            }
            w = rnd.next(max(1, edge.c - 3), min(200000, edge.c + 3));
        }

        println(u, v, w, a, b);
    }

    return 0;
}
