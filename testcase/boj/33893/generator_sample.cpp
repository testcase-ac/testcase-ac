#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 16);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        auto edge = minmax(a, b);
        if (used.insert(edge).second) {
            edges.push_back(edge);
        }
    };

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            addEdge(v - 1, v);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(1, v);
        }
    } else {
        vector<int> order;
        for (int v = 1; v <= n; ++v) {
            order.push_back(v);
        }
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(parent, order[i]);
        }
    }

    if (mode == 2) {
        for (int v = 1; v <= n; ++v) {
            addEdge(v, v == n ? 1 : v + 1);
        }
    } else if (mode == 3) {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                addEdge(a, b);
            }
        }
    } else if (mode == 4) {
        int hubA = rnd.next(1, n);
        int hubB = rnd.next(1, n);
        while (hubB == hubA) {
            hubB = rnd.next(1, n);
        }
        addEdge(hubA, hubB);
        for (int v = 1; v <= n; ++v) {
            if (v != hubA && rnd.next(0, 1)) addEdge(hubA, v);
            if (v != hubB && rnd.next(0, 1)) addEdge(hubB, v);
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.emplace_back(a, b);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = static_cast<int>(candidates.size());
    int extraEdges;
    if (mode == 5) {
        extraEdges = rnd.next(0, extraLimit);
    } else if (extraLimit == 0) {
        extraEdges = 0;
    } else {
        extraEdges = rnd.next(0, min(extraLimit, n));
    }
    for (int i = 0; i < extraEdges; ++i) {
        addEdge(candidates[i].first, candidates[i].second);
    }

    shuffle(edges.begin(), edges.end());

    vector<int> positions;
    for (int v = 2; v <= n; ++v) {
        positions.push_back(v);
    }
    shuffle(positions.begin(), positions.end());
    int k = rnd.next(1, n - 1);
    positions.resize(k);
    sort(positions.begin(), positions.end());

    println(n, static_cast<int>(edges.size()), k);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }
    println(positions);

    return 0;
}
