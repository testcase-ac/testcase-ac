#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 15);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v) {
        if (u == v) {
            return;
        }
        auto edge = minmax(u, v);
        if (used.insert(edge).second) {
            edges.push_back({u, v});
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 15);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            addEdge(center, i);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        for (int i = 1; i <= n; ++i) {
            addEdge(i, i == n ? 1 : i + 1);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 15);
        int left = rnd.next(1, n - 1);
        double density = rnd.next(0.25, 0.85);
        for (int u = 1; u <= left; ++u) {
            for (int v = left + 1; v <= n; ++v) {
                if (rnd.next() < density) {
                    addEdge(u, v);
                }
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 15);
        double density = rnd.next(0.05, 0.45);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) {
                    addEdge(u, v);
                }
            }
        }
    } else {
        n = rnd.next(4, 15);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < 0.75) {
                    addEdge(u, v);
                }
            }
        }
    }

    vector<int> label(n + 1);
    vector<int> perm;
    for (int i = 1; i <= n; ++i) {
        perm.push_back(i);
    }
    shuffle(perm.begin(), perm.end());
    for (int i = 1; i <= n; ++i) {
        label[i] = perm[i - 1];
    }

    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
