#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 14);
    int b = rnd.next(1, 40);
    int e = rnd.next(1, 40);
    int p = rnd.next(1, 40);

    int mode = rnd.next(5);
    if (mode == 0) {
        p = rnd.next(1, max(1, min(b, e)));
    } else if (mode == 1) {
        p = rnd.next(b + e, min(40000, b + e + 80));
    } else if (mode == 2) {
        b = rnd.next(1, 8);
        e = rnd.next(30, 80);
    } else if (mode == 3) {
        b = rnd.next(30, 80);
        e = rnd.next(1, 8);
    }

    vector<pair<int, int>> edges;
    auto add_edge = [&](int u, int v) {
        if (u > v) swap(u, v);
        edges.push_back({u, v});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            add_edge(i, i + 1);
        }
    } else if (mode == 1) {
        add_edge(1, n);
        add_edge(2, n);
        for (int v = 3; v < n; ++v) {
            add_edge(v, rnd.next(1, v - 1));
        }
    } else if (mode == 2) {
        int meet = rnd.next(3, n);
        add_edge(1, meet);
        add_edge(2, meet);
        for (int v = 3; v <= n; ++v) {
            if (v != meet) {
                add_edge(meet, v);
            }
        }
    } else {
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) {
            vertices.push_back(i);
        }
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < n; ++i) {
            add_edge(vertices[i], vertices[rnd.next(i)]);
        }
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extra = rnd.next(0, min<int>(candidates.size(), n + 6));
    for (int i = 0; i < extra; ++i) {
        edges.push_back(candidates[i]);
    }

    if (!edges.empty() && rnd.next(3) == 0) {
        int duplicate_count = rnd.next(1, min<int>(3, edges.size()));
        for (int i = 0; i < duplicate_count; ++i) {
            edges.push_back(rnd.any(edges));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(b, e, p, n, static_cast<int>(edges.size()));
    for (auto [u, v] : edges) {
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        println(u, v);
    }

    return 0;
}
