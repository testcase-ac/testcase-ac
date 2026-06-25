#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
                    long long w) {
    if (u > v) {
        swap(u, v);
    }
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, w});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    int p = rnd.next(1, n);
    int g = rnd.next(1, n - 1);
    if (g >= p) {
        ++g;
    }

    vector<Edge> edges;
    set<pair<int, int>> used;

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(i)];
            long long w = rnd.next(1, 20);
            addEdge(edges, used, parent, vertices[i], w);
        }
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            long long w = rnd.next(1, 15);
            addEdge(edges, used, vertices[i], vertices[i + 1], w);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            if (i != g) {
                long long w = (i == p ? rnd.next(1, 6) : rnd.next(1, 30));
                addEdge(edges, used, g, i, w);
            }
        }
    }

    if (mode == 2 && n >= 4) {
        int a = p;
        int b = g;
        int c = rnd.next(1, n);
        while (c == a || c == b) {
            c = rnd.next(1, n);
        }
        int d = rnd.next(1, n);
        while (d == a || d == b || d == c) {
            d = rnd.next(1, n);
        }
        long long x = rnd.next(1, 9);
        addEdge(edges, used, a, c, x);
        addEdge(edges, used, c, b, x);
        addEdge(edges, used, a, d, x);
        addEdge(edges, used, d, b, x);
    }

    if (mode == 3 && n >= 3) {
        for (int i = 0; i < n; ++i) {
            int u = vertices[i];
            int v = vertices[(i + 1) % n];
            addEdge(edges, used, u, v, rnd.next(1, 25));
        }
    }

    double density = mode == 4 ? rnd.next(0.45, 0.8) : rnd.next(0.05, 0.35);
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v}) && rnd.next() < density) {
                long long w;
                if (rnd.next(4) == 0) {
                    w = 1000000000LL - rnd.next(0, 20);
                } else {
                    w = rnd.next(1, 40);
                }
                addEdge(edges, used, u, v, w);
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    for (Edge& edge : edges) {
        if (rnd.next(2) == 0) {
            swap(edge.u, edge.v);
        }
    }

    println(n, static_cast<int>(edges.size()));
    println(p, g);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
