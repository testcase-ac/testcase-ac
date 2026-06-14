#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static void addEdge(vector<Edge>& edges, int u, int v, int w) {
    if (rnd.next(2)) {
        swap(u, v);
    }
    edges.push_back({u, v, w});
}

static void addUniqueEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    if (u > v) {
        swap(u, v);
    }
    if (used.insert({u, v}).second) {
        addEdge(edges, u, v, w);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(10, 14);
    int p = rnd.next(3, min(6, n - 3));
    int mode = rnd.next(4);

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i + 1;
    }
    shuffle(vertices.begin(), vertices.end());

    int x = vertices[0];
    int z = vertices[1];
    vector<int> y(vertices.begin() + 2, vertices.begin() + 2 + p);
    vector<int> important;
    important.push_back(x);
    for (int v : y) {
        important.push_back(v);
    }
    important.push_back(z);

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode != 1) {
        shuffle(important.begin() + 1, important.end() - 1);
        for (int i = 0; i + 1 < (int)important.size(); ++i) {
            addUniqueEdge(edges, used, important[i], important[i + 1], rnd.next(1, 30));
        }
    } else {
        for (int i = 1; i + 1 < (int)important.size(); ++i) {
            addUniqueEdge(edges, used, important[i], important[i + 1], rnd.next(1, 30));
        }
    }

    if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.35) {
                    addUniqueEdge(edges, used, i, j, rnd.next(1, 1000));
                }
            }
        }
    } else {
        int targetUnique = rnd.next(10, min(24, n * (n - 1) / 2));
        while ((int)used.size() < targetUnique) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) {
                ++v;
            }
            addUniqueEdge(edges, used, u, v, rnd.next(1, 200));
        }
    }

    if (mode == 3) {
        int extra = rnd.next(1, 4);
        for (int i = 0; i < extra; ++i) {
            const Edge& base = rnd.any(edges);
            addEdge(edges, base.u, base.v, rnd.next(1, 1000000));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
    println(x, z);
    println(p);
    println(y);

    return 0;
}
