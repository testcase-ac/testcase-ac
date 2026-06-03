#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int c;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int c) {
    if (u == v || !used.insert({u, v}).second) return;
    edges.push_back({u, v, c});
}

int smallCost() {
    int mode = rnd.next(0, 3);
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.next(1, 1000);
    if (mode == 2) return rnd.next(4999990, 5000000);
    return rnd.next(1, 5000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 3 ? 18 : 10);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int maxEdges = min(n - 1, rnd.next(0, n + 2));
        for (int i = 0; i < maxEdges; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) v = v % n + 1;
            addEdge(edges, used, u, v, smallCost());
        }
    } else if (mode == 1) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        int good = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            addEdge(edges, used, p[i], p[(i + 1) % n], rnd.next(good, min(5000000, good + 20)));
        }

        int extra = rnd.next(0, min(n * (n - 1) - n, 3 * n));
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            int c = rnd.next() < 0.65 ? rnd.next(good + 1, min(5000000, good + 5000)) : smallCost();
            addEdge(edges, used, u, v, c);
        }
    } else if (mode == 2) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        for (int i = 0; i + 1 < n; ++i) {
            addEdge(edges, used, p[i], p[i + 1], smallCost());
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(0, n - 2);
            int b = rnd.next(a + 1, n - 1);
            addEdge(edges, used, p[a], p[b], smallCost());
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v) addEdge(edges, used, u, v, smallCost());
            }
        }
    } else if (mode == 4) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        int bottleneck = rnd.next(2, 200);
        int bottleneckEdge = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int c = (i == bottleneckEdge) ? bottleneck : rnd.next(1, bottleneck - 1);
            addEdge(edges, used, p[i], p[(i + 1) % n], c);
        }
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next() < 0.35) addEdge(edges, used, u, v, rnd.next(bottleneck, 5000000));
            }
        }
    } else {
        int split = rnd.next(1, n - 1);
        for (int u = 1; u <= split; ++u) {
            for (int v = 1; v <= split; ++v) {
                if (u != v && rnd.next() < 0.65) addEdge(edges, used, u, v, smallCost());
            }
        }
        for (int u = split + 1; u <= n; ++u) {
            for (int v = split + 1; v <= n; ++v) {
                if (u != v && rnd.next() < 0.65) addEdge(edges, used, u, v, smallCost());
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (const Edge& e : edges) println(e.u, e.v, e.c);

    return 0;
}
