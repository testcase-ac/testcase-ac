#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 14);
    int r = rnd.next(1, n);
    int mode = rnd.next(0, 3);
    set<pair<int, int>> edgeSet;

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i + 1;

    if (mode == 0) {
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < n; ++i) addEdge(edgeSet, vertices[i - 1], vertices[i]);
    } else if (mode == 1) {
        for (int v = 1; v <= n; ++v) {
            if (v != r) addEdge(edgeSet, r, v);
        }
    } else if (mode == 2) {
        shuffle(vertices.begin(), vertices.end());
        int connectedSize = rnd.next(2, n - 2);
        bool hasR = false;
        for (int i = 0; i < connectedSize; ++i) hasR |= vertices[i] == r;
        if (!hasR) {
            int rPos = 0;
            while (vertices[rPos] != r) ++rPos;
            swap(vertices[0], vertices[rPos]);
        }
        for (int i = 1; i < connectedSize; ++i) {
            addEdge(edgeSet, vertices[rnd.next(0, i - 1)], vertices[i]);
        }
        for (int i = connectedSize + 1; i < n; ++i) {
            if (rnd.next(0, 1)) addEdge(edgeSet, vertices[i - 1], vertices[i]);
        }
    } else {
        double density = rnd.next(0.25, 0.65);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) addEdge(edgeSet, u, v);
            }
        }
    }

    if (edgeSet.empty()) addEdge(edgeSet, rnd.next(1, n - 1), rnd.next(2, n));

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), r);
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
