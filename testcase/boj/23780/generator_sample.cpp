#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    auto key = minmax(u, v);
    if (used.insert(key).second) {
        if (rnd.next(2)) {
            swap(u, v);
        }
        edges.push_back({u, v, w});
    }
}

static int nextWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.next(1, 100);
    }
    return rnd.next(999990, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = 2;
    } else {
        n = rnd.next(3, 12);
    }

    int vertexWeightMode = rnd.next(3);
    int edgeWeightMode = rnd.next(3);

    vector<int> vertexWeights(n);
    for (int i = 0; i < n; ++i) {
        vertexWeights[i] = nextWeight(vertexWeightMode);
    }

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 1) {
        addEdge(edges, used, 0, 1, nextWeight(edgeWeightMode));
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i - 1, i, nextWeight(edgeWeightMode));
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, 0, i, nextWeight(edgeWeightMode));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            addEdge(edges, used, i, (i + 1) % n, nextWeight(edgeWeightMode));
        }
    } else if (mode == 5) {
        double density = rnd.next(0.25, 0.75);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) {
                    addEdge(edges, used, i, j, nextWeight(edgeWeightMode));
                }
            }
        }
        if (edges.empty()) {
            int u = rnd.next(n);
            int v = rnd.next(n - 1);
            if (v >= u) {
                ++v;
            }
            addEdge(edges, used, u, v, nextWeight(edgeWeightMode));
        }
    } else if (mode == 6) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(edges, used, i - 1, i, nextWeight(edgeWeightMode));
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(edges, used, i - 1, i, nextWeight(edgeWeightMode));
        }
        if (rnd.next(2)) {
            addEdge(edges, used, rnd.next(split), rnd.next(split, n - 1), nextWeight(edgeWeightMode));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    println(vertexWeights);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
