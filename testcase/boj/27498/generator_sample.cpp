#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

struct Edge {
    int a;
    int b;
    int c;
    int d;
};

int weightFor(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(9500, 10000);
    if (mode == 2) return rnd.next(1, 3);
    return rnd.next(1, 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = (mode == 1 ? rnd.next(5, 10) : rnd.next(3, 12));

    vector<pair<int, int>> allPairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            allPairs.push_back({a, b});
        }
    }
    shuffle(allPairs.begin(), allPairs.end());

    vector<Edge> edges;
    set<pair<int, int>> used;
    Dsu connected(n);
    Dsu established(n);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    int establishedTreeEdges = rnd.next(0, n - 1);
    if (mode == 2) establishedTreeEdges = n - 1;
    if (mode == 3) establishedTreeEdges = 0;

    for (int i = 1; i < n; ++i) {
        int a = order[i];
        int b = order[rnd.next(0, i - 1)];
        if (a > b) swap(a, b);
        int d = (i <= establishedTreeEdges ? 1 : 0);
        edges.push_back({a, b, weightFor(mode), d});
        used.insert({a, b});
        connected.unite(a, b);
        if (d == 1) established.unite(a, b);
    }

    int maxEdges = static_cast<int>(allPairs.size());
    int targetM;
    if (mode == 0) {
        targetM = rnd.next(n, min(maxEdges, n + 5));
    } else if (mode == 1) {
        targetM = rnd.next(max(n, maxEdges - n), maxEdges);
    } else if (mode == 2) {
        targetM = rnd.next(n, min(maxEdges, n + 8));
    } else {
        targetM = rnd.next(n, min(maxEdges, 2 * n));
    }

    for (auto [a, b] : allPairs) {
        if (static_cast<int>(edges.size()) == targetM) break;
        if (used.count({a, b})) continue;

        int d = 0;
        if (mode != 3 && rnd.next(0, 4) == 0 && established.unite(a, b)) {
            d = 1;
        }

        edges.push_back({a, b, weightFor(mode), d});
        used.insert({a, b});
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c, edge.d);
    }

    return 0;
}
