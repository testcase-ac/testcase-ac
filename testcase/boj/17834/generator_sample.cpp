#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

static void addPath(vector<pair<int, int>>& edges, int n) {
    for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
}

static void addRandomExtraEdges(vector<pair<int, int>>& edges, int n, int count) {
    for (int i = 0; i < count; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) ++v;
        edges.push_back({u, v});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        addPath(edges, n);
    } else if (mode == 1) {
        addPath(edges, n);
        if (n >= 3) edges.push_back({n, 1});
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) edges.push_back({center, v});
        }
        addRandomExtraEdges(edges, n, rnd.next(0, n));
    } else if (mode == 3) {
        int left = rnd.next(1, n - 1);
        vector<int> order;
        for (int i = 1; i <= n; ++i) order.push_back(i);
        shuffle(order.begin(), order.end());

        for (int i = 0; i < left; ++i) edges.push_back({order[i], order[left]});
        for (int i = left + 1; i < n; ++i) edges.push_back({order[0], order[i]});

        double density = rnd.next(0.2, 0.85);
        for (int i = 0; i < left; ++i) {
            for (int j = left; j < n; ++j) {
                if (rnd.next() < density) edges.push_back({order[i], order[j]});
            }
        }
    } else if (mode == 4) {
        addPath(edges, n);
        double density = rnd.next(0.25, 0.75);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) edges.push_back({u, v});
            }
        }
    } else if (mode == 5) {
        addPath(edges, n);
        int base = rnd.next(1, n - 1);
        int copies = rnd.next(1, 10);
        for (int i = 0; i < copies; ++i) edges.push_back({base, base + 1});
        addRandomExtraEdges(edges, n, rnd.next(0, n / 2));
    } else {
        int clique = rnd.next(2, n);
        for (int u = 1; u <= clique; ++u) {
            for (int v = u + 1; v <= clique; ++v) edges.push_back({u, v});
        }
        for (int v = clique + 1; v <= n; ++v) edges.push_back({rnd.next(1, v - 1), v});
        addRandomExtraEdges(edges, n, rnd.next(0, n));
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
