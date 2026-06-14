#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static void addEdge(vector<pair<int, int>>& edges, int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    edges.push_back({u, v});
}

static vector<int> shuffledLabels(int n) {
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    return label;
}

static vector<pair<int, int>> buildShape(int n, int mode) {
    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                addEdge(edges, center, i);
            }
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, i / 2, i);
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i, i + 1);
        }
        for (int i = spine + 1; i <= n; ++i) {
            addEdge(edges, rnd.next(1, spine), i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, rnd.next(1, i - 1), i);
        }
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    if (mode == 2) {
        n = rnd.next(3, 15);
    }

    int m;
    if (rnd.next(0, 3) == 0) {
        m = 2;
    } else {
        m = rnd.next(2, min(20, n + 6));
    }
    int q = rnd.next(1, 30);

    vector<pair<int, int>> rawEdges = buildShape(n, mode);
    vector<int> label = shuffledLabels(n);
    vector<Edge> edges;
    set<pair<int, int>> seen;
    for (auto [u, v] : rawEdges) {
        u = label[u];
        v = label[v];
        if (u > v) {
            swap(u, v);
        }
        ensure(seen.insert({u, v}).second);

        int color;
        if (rnd.next(0, 4) == 0) {
            color = 1 + ((int)edges.size() % min(m, 3));
        } else if (rnd.next(0, 3) == 0) {
            color = rnd.next(1, min(m, 3));
        } else {
            color = rnd.next(1, m);
        }
        edges.push_back({u, v, color});
    }

    if (rnd.next(0, 1)) {
        shuffle(edges.begin(), edges.end());
    }

    println(n, m, q);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    for (int i = 0; i < q; ++i) {
        int p;
        if (i > 0 && rnd.next(0, 2) == 0) {
            p = rnd.next(1, min(n - 1, 3));
        } else {
            p = rnd.next(1, n - 1);
        }

        int color;
        if (rnd.next(0, 4) == 0) {
            color = edges[p - 1].w;
        } else if (rnd.next(0, 2) == 0) {
            color = rnd.next(1, min(m, 3));
        } else {
            color = rnd.next(1, m);
        }
        edges[p - 1].w = color;
        println(p, color);
    }

    return 0;
}
