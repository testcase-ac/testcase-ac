#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 3 ? 18 : 30);
    set<pair<int, int>> edge_set;

    auto add_edge = [&](int u, int v) {
        if (u == v) return;
        if (u > v) swap(u, v);
        edge_set.insert({u, v});
    };

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            add_edge(v, rnd.next(1, v - 1));
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            add_edge(v, rnd.next(1, v - 1));
        }
        int extra_limit = n * (n - 1) / 2 - (n - 1);
        int extra = extra_limit == 0 ? 0 : rnd.next(1, min(2 * n, extra_limit));
        while (extra-- > 0) {
            add_edge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        int components = rnd.next(2, min(n, 5));
        for (int v = components + 1; v <= n; ++v) {
            add_edge(v, rnd.next(1, v - 1));
        }
        int extra = rnd.next(1, n);
        while (extra-- > 0) {
            add_edge(rnd.next(1, n), rnd.next(1, n));
        }
        if (edge_set.empty()) add_edge(1, 2);
    } else if (mode == 3) {
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < rnd.next(25, 75)) {
                    add_edge(u, v);
                }
            }
        }
        if (edge_set.empty()) add_edge(1, 2);
    } else {
        int chain = rnd.next(2, n);
        for (int v = 1; v < chain; ++v) add_edge(v, v + 1);
        for (int v = chain + 1; v <= n; ++v) {
            add_edge(v, rnd.next(max(1, chain - 2), v - 1));
        }
        int triangles = rnd.next(0, max(0, n / 3));
        while (triangles-- > 0) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            int c = rnd.next(1, n);
            add_edge(a, b);
            add_edge(b, c);
            add_edge(a, c);
        }
    }

    vector<pair<int, int>> edges(edge_set.begin(), edge_set.end());
    shuffle(edges.begin(), edges.end());

    int k = rnd.next(1, n);
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i + 1;
    shuffle(vertices.begin(), vertices.end());
    vertices.resize(k);

    int c = rnd.next(0, 1);

    println(n, static_cast<int>(edges.size()), k);
    for (auto [u, v] : edges) println(u, v);
    for (int x : vertices) println(x);
    println(c);

    return 0;
}
