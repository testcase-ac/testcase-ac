#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

static vector<int> shuffledVertices(int n) {
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());
    return vertices;
}

static vector<int> takeDistinctVertices(const vector<int>& order, int p) {
    vector<int> values(order.begin(), order.begin() + p);
    shuffle(values.begin(), values.end());
    return values;
}

static void addEdge(vector<pair<int, int>>& edges, vector<vector<int>>& used, int u, int v) {
    if (u == v || used[u][v]) {
        return;
    }
    used[u][v] = 1;
    edges.push_back({u, v});
}

static void addRandomEdges(vector<pair<int, int>>& edges, vector<vector<int>>& used, int n, int attempts) {
    for (int i = 0; i < attempts; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        addEdge(edges, used, u, v);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 14 : 10);
    vector<pair<int, int>> edges;
    vector<vector<int>> used(n + 1, vector<int>(n + 1, 0));

    if (mode == 0) {
        addRandomEdges(edges, used, n, rnd.next(0, n));
    } else if (mode == 1) {
        vector<int> order = shuffledVertices(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 99) < 35) {
                    addEdge(edges, used, order[i], order[j]);
                }
            }
        }
    } else if (mode == 2) {
        vector<int> order = shuffledVertices(n);
        int cycleSize = rnd.next(1, n);
        if (cycleSize > 1) {
            for (int i = 0; i < cycleSize; ++i) {
                addEdge(edges, used, order[i], order[(i + 1) % cycleSize]);
            }
        }
        addRandomEdges(edges, used, n, rnd.next(n, 2 * n));
    } else if (mode == 3) {
        vector<int> order = shuffledVertices(n);
        int split = rnd.next(1, n);
        for (int i = 0; i + 1 < split; ++i) {
            addEdge(edges, used, order[i], order[i + 1]);
        }
        if (split > 1) {
            addEdge(edges, used, order[split - 1], order[0]);
        }
        for (int i = split; i + 1 < n; ++i) {
            addEdge(edges, used, order[i], order[i + 1]);
        }
        addRandomEdges(edges, used, n, rnd.next(0, n));
    } else {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next(0, 99) < 45) {
                    addEdge(edges, used, u, v);
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    int p;
    if (rnd.next(0, 9) == 0) {
        p = 0;
    } else if (rnd.next(0, 9) == 0) {
        p = n;
    } else {
        p = rnd.next(1, n);
    }

    vector<int> redOrder = shuffledVertices(n);
    vector<int> blueOrder = redOrder;
    if (rnd.next(0, 1)) {
        shuffle(blueOrder.begin(), blueOrder.end());
    } else if (p > 1) {
        rotate(blueOrder.begin(), blueOrder.begin() + rnd.next(1, p), blueOrder.begin() + p);
    }

    vector<int> red = takeDistinctVertices(redOrder, p);
    vector<int> blue = takeDistinctVertices(blueOrder, p);

    println(n, static_cast<int>(edges.size()));
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }
    println(p);
    println(red);
    println(blue);

    return 0;
}
