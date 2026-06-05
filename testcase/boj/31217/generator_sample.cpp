#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 14);
    set<pair<int, int>> seen;
    vector<pair<int, int>> edges;

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        auto edge = minmax(u, v);
        if (seen.insert(edge).second) {
            edges.push_back({u, v});
        }
    };

    if (mode == 0) {
        int target = rnd.next(0, min(3, n * (n - 1) / 2));
        while ((int)edges.size() < target) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 14);
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center && rnd.next(0, 4) != 0) {
                addEdge(center, v);
            }
        }
        int extras = rnd.next(0, min(5, n));
        for (int i = 0; i < extras; ++i) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        int k = rnd.next(3, n);
        for (int i = 1; i <= k; ++i) {
            for (int j = i + 1; j <= k; ++j) {
                addEdge(i, j);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        int left = rnd.next(1, n - 1);
        double p = rnd.next(0.25, 0.9);
        for (int u = 1; u <= left; ++u) {
            for (int v = left + 1; v <= n; ++v) {
                if (rnd.next() < p) {
                    addEdge(u, v);
                }
            }
        }
    } else if (mode == 4) {
        n = rnd.next(4, 14);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
        if (rnd.next(0, 1)) {
            addEdge(n, 1);
        }
        int chords = rnd.next(0, min(4, n));
        for (int i = 0; i < chords; ++i) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 14);
        int hubs = rnd.next(2, min(4, n));
        for (int u = 1; u <= hubs; ++u) {
            for (int v = hubs + 1; v <= n; ++v) {
                if (rnd.next(0, 3) != 0) {
                    addEdge(u, v);
                }
            }
        }
        for (int u = 1; u <= hubs; ++u) {
            for (int v = u + 1; v <= hubs; ++v) {
                if (rnd.next(0, 1)) {
                    addEdge(u, v);
                }
            }
        }
    } else {
        n = rnd.next(2, 14);
        double p = rnd.next(0.05, 0.75);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < p) {
                    addEdge(i, j);
                }
            }
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v);
    }

    return 0;
}
