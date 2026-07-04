#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u == v) {
        return;
    }
    if (u > v) {
        swap(u, v);
    }
    edges.insert({u, v});
}

void emitGraph(int n, const set<pair<int, int>>& edges) {
    println(n, static_cast<int>(edges.size()));
    for (auto [u, v] : edges) {
        println(u, v);
    }
}

set<pair<int, int>> randomSimpleGraph(int n, int targetEdges) {
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }

    shuffle(candidates.begin(), candidates.end());
    targetEdges = min(targetEdges, static_cast<int>(candidates.size()));
    return set<pair<int, int>>(candidates.begin(), candidates.begin() + targetEdges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(4, 8);
    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(0, 6);
        set<pair<int, int>> edges;

        if (mode == 0) {
            int n = rnd.next(0, 2);
            emitGraph(n, edges);
        } else if (mode == 1) {
            int n = rnd.next(2, 12);
            for (int i = 1; i < n; ++i) {
                addEdge(edges, i, i + 1);
            }
            emitGraph(n, edges);
        } else if (mode == 2) {
            int n = rnd.next(3, 12);
            for (int i = 1; i <= n; ++i) {
                addEdge(edges, i, i == n ? 1 : i + 1);
            }
            emitGraph(n, edges);
        } else if (mode == 3) {
            int leaves = rnd.next(1, 8);
            int n = leaves + 1;
            for (int v = 2; v <= n; ++v) {
                addEdge(edges, 1, v);
            }
            emitGraph(n, edges);
        } else if (mode == 4) {
            int n = rnd.next(4, 7);
            emitGraph(n, randomSimpleGraph(n, n * (n - 1) / 2));
        } else if (mode == 5) {
            int n = rnd.next(6, 14);
            int maxEdges = n * (n - 1) / 2;
            int targetEdges = rnd.next(n - 1, min(maxEdges, n + 10));
            emitGraph(n, randomSimpleGraph(n, targetEdges));
        } else {
            int n = rnd.next(6, 12);
            addEdge(edges, 1, 2);
            addEdge(edges, 1, 3);
            addEdge(edges, 1, 4);
            addEdge(edges, 2, 5);
            addEdge(edges, 2, 6);
            if (rnd.next(0, 1)) {
                addEdge(edges, 1, 2);
            }
            for (int v = 7; v <= n; ++v) {
                addEdge(edges, rnd.next(1, v - 1), v);
            }
            emitGraph(n, edges);
        }
    }

    return 0;
}
