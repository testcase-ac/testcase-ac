#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 12 : 8);
    int k = rnd.next(1, mode == 0 ? 3 : 10);

    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            pairs.push_back({a, b});
        }
    }
    shuffle(pairs.begin(), pairs.end());

    vector<Edge> edges;

    auto addEdge = [&](int a, int b) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        edges.push_back({a, b, 0});
    };

    if (mode == 0) {
        // Small forest with a few extra parallel candidates.
        for (int v = 2; v <= n; ++v) {
            if (rnd.next(0, 99) < 75) {
                addEdge(v, rnd.next(1, v - 1));
            }
        }
        int extra = rnd.next(0, min(5, n));
        for (int i = 0; i < extra; ++i) {
            auto [a, b] = rnd.any(pairs);
            addEdge(a, b);
        }
    } else if (mode == 1) {
        // One prominent cycle, then a few chords.
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            addEdge(order[i], order[(i + 1) % n]);
        }
        int chords = rnd.next(0, min(6, static_cast<int>(pairs.size())));
        for (int i = 0; i < chords; ++i) {
            addEdge(pairs[i].first, pairs[i].second);
        }
    } else if (mode == 2) {
        // Several parallel railways between the same city pairs.
        int basePairs = rnd.next(1, min(4, static_cast<int>(pairs.size())));
        for (int i = 0; i < basePairs; ++i) {
            int copies = rnd.next(2, 5);
            for (int j = 0; j < copies; ++j) {
                addEdge(pairs[i].first, pairs[i].second);
            }
        }
    } else if (mode == 3) {
        // Dense simple graph on a small number of cities.
        int take = rnd.next(n - 1, min(static_cast<int>(pairs.size()), n + 8));
        for (int i = 0; i < take; ++i) {
            addEdge(pairs[i].first, pairs[i].second);
        }
    } else {
        // Mixed medium case with cycles, parallels, and varied K.
        int take = rnd.next(1, min(static_cast<int>(pairs.size()), 18));
        for (int i = 0; i < take; ++i) {
            addEdge(pairs[i].first, pairs[i].second);
            if (rnd.next(0, 99) < 30) {
                addEdge(pairs[i].first, pairs[i].second);
            }
        }
        k = rnd.next(1, 25);
    }

    if (edges.empty()) {
        addEdge(1, 2);
    }

    vector<int> profits;
    int base = rnd.next(1, 1000000000 - 1000000);
    int step = rnd.next(1, 997);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        profits.push_back(base + i * step);
    }
    shuffle(profits.begin(), profits.end());
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        edges[i].c = profits[i];
    }
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), k);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c);
    }

    return 0;
}
