#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

static void addEdge(set<Edge>& edges, int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    edges.insert({u, v});
}

static int id(int row, int col, int width) {
    return row * width + col + 1;
}

static vector<int> shuffledLabels(int vertexCount) {
    vector<int> labels(vertexCount + 1);
    for (int i = 1; i <= vertexCount; ++i) {
        labels[i] = i;
    }
    shuffle(labels.begin() + 1, labels.end());
    return labels;
}

static set<Edge> makeGrid(int n, int m) {
    set<Edge> edges;
    vector<int> label = shuffledLabels(n * m);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (r + 1 < n) {
                addEdge(edges, label[id(r, c, m)], label[id(r + 1, c, m)]);
            }
            if (c + 1 < m) {
                addEdge(edges, label[id(r, c, m)], label[id(r, c + 1, m)]);
            }
        }
    }
    return edges;
}

static set<Edge> makeCycleHeavyGraph(int vertexCount, int edgeCount) {
    set<Edge> edges;

    for (int i = 1; i <= vertexCount; ++i) {
        addEdge(edges, i, i % vertexCount + 1);
    }
    while (static_cast<int>(edges.size()) < edgeCount) {
        int u = rnd.next(1, vertexCount);
        int v = rnd.next(1, vertexCount);
        if (u != v) {
            addEdge(edges, u, v);
        }
    }
    return edges;
}

static set<Edge> makeDisconnectedGraph(int vertexCount, int edgeCount) {
    set<Edge> edges;

    for (int i = 1; i < vertexCount - 1; ++i) {
        addEdge(edges, i, i + 1);
    }

    while (static_cast<int>(edges.size()) < edgeCount) {
        int u = rnd.next(1, vertexCount - 1);
        int v = rnd.next(1, vertexCount - 1);
        if (u != v) {
            addEdge(edges, u, v);
        }
    }
    return edges;
}

static set<Edge> makeDegreeTrapGraph(int vertexCount, int edgeCount) {
    set<Edge> edges;
    int hub = rnd.next(1, vertexCount);

    for (int v = 1; v <= vertexCount; ++v) {
        if (v != hub) {
            addEdge(edges, hub, v);
        }
    }

    while (static_cast<int>(edges.size()) < edgeCount) {
        int u = rnd.next(1, vertexCount);
        int v = rnd.next(1, vertexCount);
        if (u != v) {
            addEdge(edges, u, v);
        }
    }
    return edges;
}

static void printCase(int n, int m, const set<Edge>& edges) {
    println(n, m);
    vector<Edge> ordered(edges.begin(), edges.end());
    shuffle(ordered.begin(), ordered.end());
    for (const auto& edge : ordered) {
        println(edge.first, edge.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int m = rnd.next(2, 10);
    int vertexCount = n * m;
    int edgeCount = n * (m - 1) + (n - 1) * m;

    int mode = rnd.next(0, 3);
    set<Edge> edges;
    if (mode == 0) {
        edges = makeGrid(n, m);
    } else if (mode == 1) {
        edges = makeCycleHeavyGraph(vertexCount, edgeCount);
    } else if (vertexCount >= 6 && mode == 2) {
        edges = makeDisconnectedGraph(vertexCount, edgeCount);
    } else {
        edges = makeDegreeTrapGraph(vertexCount, edgeCount);
    }

    printCase(n, m, edges);
    return 0;
}
