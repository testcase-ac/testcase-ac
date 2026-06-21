#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int d;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int d) {
    if (u > v) swap(u, v);
    if (used.emplace(u, v).second) {
        edges.push_back({u, v, d});
    }
}

int weightForMode(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 1000);
    if (mode == 2) return rnd.next(999999900, 1000000000);
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(4, 16);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int m = rnd.next(0, min(6, n * (n - 1) / 2));
        for (int tries = 0; (int)edges.size() < m && tries < 200; ++tries) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v) continue;
            addEdge(edges, used, u, v, weightForMode(rnd.next(0, 3)));
        }
    } else if (mode == 1) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        int len = rnd.next(4, min(n, 8));
        for (int i = 0; i + 1 < len; ++i) {
            addEdge(edges, used, p[i], p[i + 1], rnd.next(50, 1000));
        }
        int extras = rnd.next(0, min(10, n));
        for (int i = 0; i < extras; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u != v) addEdge(edges, used, u, v, rnd.next(1, 200));
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        vector<int> leaves;
        for (int i = 1; i <= n; ++i) {
            if (i != center) leaves.push_back(i);
        }
        shuffle(leaves.begin(), leaves.end());

        int degree = rnd.next(3, min((int)leaves.size(), 8));
        for (int i = 0; i < degree; ++i) {
            addEdge(edges, used, center, leaves[i], rnd.next(100, 10000));
        }
        for (int i = 0; i + 1 < degree; ++i) {
            if (rnd.next(0, 1)) addEdge(edges, used, leaves[i], leaves[i + 1], rnd.next(1, 500));
        }
    } else if (mode == 3) {
        int limit = min(10, n);
        for (int u = 1; u <= limit; ++u) {
            for (int v = u + 1; v <= limit; ++v) {
                if (rnd.next(0, 99) < rnd.next(35, 80)) {
                    addEdge(edges, used, u, v, weightForMode(rnd.next(0, 3)));
                }
            }
        }
    } else if (mode == 4) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        addEdge(edges, used, p[0], p[1], rnd.next(900000000, 1000000000));
        addEdge(edges, used, p[2], p[3], rnd.next(900000000, 1000000000));
        int extras = rnd.next(0, 8);
        for (int i = 0; i < extras; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u != v) addEdge(edges, used, u, v, rnd.next(1, 1000));
        }
    } else {
        int leftSize = rnd.next(2, n - 2);
        vector<int> ids(n);
        for (int i = 0; i < n; ++i) ids[i] = i + 1;
        shuffle(ids.begin(), ids.end());

        for (int i = 0; i < leftSize; ++i) {
            for (int j = leftSize; j < n; ++j) {
                if (rnd.next(0, 99) < 35) {
                    addEdge(edges, used, ids[i], ids[j], weightForMode(rnd.next(0, 3)));
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& e : edges) {
        println(e.u, e.v, e.d);
    }

    return 0;
}
