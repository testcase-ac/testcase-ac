#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int maxEdgeOnPath(int cur, int target, int parent,
                  const vector<vector<pair<int, int>>>& tree) {
    if (cur == target) {
        return 0;
    }
    for (auto [next, weight] : tree[cur]) {
        if (next == parent) {
            continue;
        }
        int sub = maxEdgeOnPath(next, target, cur, tree);
        if (sub != -1) {
            return max(weight, sub);
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int mode = rnd.next(4);
    int maxEdges = n * (n - 1) / 2;
    int extraLimit = maxEdges - (n - 1);
    int extraEdges = 0;
    if (extraLimit > 0) {
        if (mode == 0) {
            extraEdges = rnd.next(0, min(extraLimit, n / 2));
        } else if (mode == 1) {
            extraEdges = rnd.next(0, min(extraLimit, n));
        } else if (mode == 2) {
            extraEdges = rnd.next(0, min(extraLimit, 2 * n));
        } else {
            extraEdges = rnd.next(max(0, extraLimit - n), extraLimit);
        }
    }

    vector<tuple<int, int, int>> edges;
    vector<vector<pair<int, int>>> tree(n);
    set<pair<int, int>> used;

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    int baseWeight = rnd.next(1, 25);
    for (int i = 1; i < n; ++i) {
        int parentIndex;
        if (mode == 0) {
            parentIndex = 0;
        } else if (mode == 1) {
            parentIndex = i - 1;
        } else {
            parentIndex = rnd.next(0, i - 1);
        }

        int u = order[i];
        int v = order[parentIndex];
        if (u > v) {
            swap(u, v);
        }
        int weight = baseWeight + rnd.next(0, 20) + i * rnd.next(1, 8);
        used.insert({u, v});
        edges.emplace_back(u, v, weight);
        tree[u].push_back({v, weight});
        tree[v].push_back({u, weight});
    }

    vector<pair<int, int>> candidates;
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (!used.count({u, v})) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(extraEdges);

    for (auto [u, v] : candidates) {
        int pathMax = maxEdgeOnPath(u, v, -1, tree);
        int weight = pathMax + rnd.next(1, 100);
        edges.emplace_back(u, v, weight);
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (auto [u, v, weight] : edges) {
        if (rnd.next(2) == 1) {
            swap(u, v);
        }
        println(u, v, weight);
    }

    return 0;
}
