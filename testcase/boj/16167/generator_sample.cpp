#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
    int d;
    int e;
};

Edge randomEdge(int n) {
    return {rnd.next(1, n), rnd.next(1, n), rnd.next(1, 20), rnd.next(1, 20),
            rnd.next(1, 35)};
}

Edge pricedEdge(int a, int b, int baseCost) {
    int e = rnd.next(1, 25);
    int d = rnd.next(1, 8);
    int c = baseCost;
    if (e > 10) {
        int extra = d * (e - 10);
        c = max(1, baseCost - extra);
    }
    c = min(c, 100);
    return {a, b, c, d, e};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    if (mode == 0) {
        int middle = rnd.next(2, n);
        for (int v = 1; v < middle; ++v) {
            edges.push_back({v, v + 1, rnd.next(1, 15), rnd.next(1, 7),
                             rnd.next(1, 22)});
        }
        if (middle != n) {
            edges.push_back({n, rnd.next(1, n - 1), rnd.next(1, 20),
                             rnd.next(1, 10), rnd.next(1, 30)});
        }
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) {
            edges.push_back({v, v + 1, rnd.next(1, 20), rnd.next(1, 10),
                             rnd.next(1, 30)});
        }
        int extra = rnd.next(0, min(30, n * 3));
        for (int i = 0; i < extra; ++i) {
            edges.push_back(randomEdge(n));
        }
    } else if (mode == 2) {
        n = max(n, 4);
        int cost = rnd.next(8, 30);
        edges.push_back(pricedEdge(1, n, cost));
        edges.push_back(pricedEdge(1, 2, cost / 2));
        edges.push_back(pricedEdge(2, n, cost - cost / 2));
        for (int v = 3; v < n; ++v) {
            edges.push_back({1, v, rnd.next(1, 10), rnd.next(1, 8),
                             rnd.next(1, 25)});
            edges.push_back({v, n, rnd.next(1, 10), rnd.next(1, 8),
                             rnd.next(1, 25)});
        }
    } else if (mode == 3) {
        int limit = min(n, rnd.next(2, 5));
        for (int a = 1; a <= limit; ++a) {
            for (int b = 1; b <= limit; ++b) {
                if (rnd.next(0, 3) != 0) {
                    edges.push_back({a, b, rnd.next(1, 12), rnd.next(1, 12),
                                     rnd.next(1, 35)});
                }
            }
        }
        edges.push_back({limit, n, rnd.next(1, 15), rnd.next(1, 10),
                         rnd.next(1, 25)});
    } else {
        int r = rnd.next(1, 45);
        for (int i = 0; i < r; ++i) {
            edges.push_back(randomEdge(n));
        }
    }

    if (rnd.next(0, 2) == 0 && static_cast<int>(edges.size()) < 198) {
        int repeats = rnd.next(1, 3);
        for (int i = 0; i < repeats && static_cast<int>(edges.size()) < 200; ++i) {
            Edge e = rnd.any(edges);
            e.c = rnd.next(1, 25);
            e.d = rnd.next(1, 15);
            e.e = rnd.next(1, 40);
            edges.push_back(e);
        }
    }

    shuffle(edges.begin(), edges.end());
    if (edges.empty()) {
        edges.push_back(randomEdge(n));
    }
    if (static_cast<int>(edges.size()) > 200) {
        edges.resize(200);
    }

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c, edge.d, edge.e);
    }

    return 0;
}
