#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode >= 2 ? rnd.next(4, 14) : rnd.next(3, 14));
    int maxEdges = n * (n - 1) / 2;

    int targetM;
    if (mode == 0) {
        targetM = n - 1;
    } else if (mode == 1) {
        targetM = n;
    } else if (mode == 2) {
        targetM = min(maxEdges, n + rnd.next(1, min(4, maxEdges - n)));
    } else if (mode == 3) {
        targetM = rnd.next(n - 1, min(maxEdges, n + 3));
    } else if (mode == 4) {
        targetM = rnd.next(n + 1, min(maxEdges, 2 * n));
    } else {
        n = rnd.next(4, 8);
        maxEdges = n * (n - 1) / 2;
        targetM = rnd.next(max(n + 1, maxEdges - 3), maxEdges);
    }

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v) {
        if (u > v) {
            swap(u, v);
        }
        if (used.insert({u, v}).second) {
            edges.push_back({u, v});
        }
    };

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    if (mode == 1 && rnd.next(0, 1) == 0) {
        for (int i = 0; i < n; ++i) {
            addEdge(order[i], order[(i + 1) % n]);
        }
    } else {
        for (int i = 1; i < n; ++i) {
            addEdge(order[i], order[rnd.next(0, i - 1)]);
        }
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto edge : candidates) {
        if (static_cast<int>(edges.size()) >= targetM) {
            break;
        }
        addEdge(edge.first, edge.second);
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v);
    }

    return 0;
}
