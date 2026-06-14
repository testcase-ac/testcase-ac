#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 30);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v - 1, v);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.emplace_back(center, v);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.emplace_back(v - 1, v);
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, spine), v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            edges.emplace_back(parent, v);
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(edge.first, edge.second);
        }
    }

    int m = rnd.next(1, min(60, 2 * n));
    vector<pair<int, int>> queries;
    queries.reserve(m);
    for (int i = 0; i < m; ++i) {
        auto edge = rnd.any(edges);
        if (rnd.next(0, 1) == 1) {
            swap(edge.first, edge.second);
        }
        queries.push_back(edge);
    }

    println(n, m);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    for (const auto& query : queries) {
        int color = rnd.next(0, 1);
        println(query.first, query.second, color);
    }

    return 0;
}
