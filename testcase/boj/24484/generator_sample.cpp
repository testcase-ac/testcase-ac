#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u == v) return;
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 15);
    int r = rnd.next(1, n);
    set<pair<int, int>> edges;

    if (mode == 0) {
        r = rnd.next(1, n);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 1) {
        r = rnd.next(1, n);
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) addEdge(edges, center, v);
        }
    } else if (mode == 2) {
        r = rnd.next(1, n / 2);
        for (int i = 1; i < n / 2; ++i) addEdge(edges, i, i + 1);
        for (int i = n / 2 + 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 3) {
        int split = rnd.next(2, n - 2);
        r = rnd.next(1, n);
        for (int i = 1; i <= split; ++i) {
            for (int j = i + 1; j <= split; ++j) addEdge(edges, i, j);
        }
        for (int i = split + 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 4) {
        r = rnd.next(1, n);
        for (int i = 2; i <= n; ++i) addEdge(edges, rnd.next(1, i - 1), i);
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) addEdge(edges, rnd.next(1, n), rnd.next(1, n));
    } else {
        r = rnd.next(1, n);
        double p = rnd.next(0.20, 0.65);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < p) addEdge(edges, i, j);
            }
        }
    }

    while (edges.empty()) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u != v) addEdge(edges, u, v);
    }

    vector<pair<int, int>> out(edges.begin(), edges.end());
    shuffle(out.begin(), out.end());

    println(n, static_cast<int>(out.size()), r);
    for (const auto& [u, v] : out) println(u, v);

    return 0;
}
