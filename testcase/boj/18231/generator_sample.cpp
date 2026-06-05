#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 12);

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    set<pair<int, int>> used;
    auto addEdge = [&](int a, int b) {
        if (a == b) {
            return;
        }
        if (a > b) {
            swap(a, b);
        }
        used.insert({a, b});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            addEdge(center, i);
        }
        int extra = rnd.next(0, n / 2);
        while (extra--) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        int clique = rnd.next(2, n);
        for (int i = 1; i <= clique; ++i) {
            for (int j = i + 1; j <= clique; ++j) {
                addEdge(i, j);
            }
        }
        for (int i = clique + 1; i <= n; ++i) {
            addEdge(i, rnd.next(1, i - 1));
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            addEdge(i, rnd.next(1, n));
        }
        int extra = rnd.next(n, 2 * n);
        while (extra--) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        double density = mode == 4 ? rnd.next(0.10, 0.40) : rnd.next(0.55, 0.95);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) {
                    addEdge(i, j);
                }
            }
        }
    }

    if (used.empty()) {
        addEdge(1, 2);
    }

    vector<vector<int>> graph(n + 1);
    vector<pair<int, int>> edges;
    for (auto [u, v] : used) {
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({label[u], label[v]});
    }

    vector<int> bombs;
    int bombCount = rnd.next(1, max(1, n / 3));
    vector<int> vertices;
    for (int i = 1; i <= n; ++i) {
        vertices.push_back(i);
    }
    shuffle(vertices.begin(), vertices.end());
    for (int i = 0; i < bombCount; ++i) {
        bombs.push_back(vertices[i]);
    }

    vector<bool> destroyedRaw(n + 1, false);
    for (int b : bombs) {
        destroyedRaw[b] = true;
        for (int v : graph[b]) {
            destroyedRaw[v] = true;
        }
    }

    if (rnd.next(0, 3) == 0) {
        int v = rnd.next(1, n);
        destroyedRaw[v] = !destroyedRaw[v];
    }

    vector<int> destroyed;
    for (int i = 1; i <= n; ++i) {
        if (destroyedRaw[i]) {
            destroyed.push_back(label[i]);
        }
    }
    if (destroyed.empty()) {
        destroyed.push_back(label[rnd.next(1, n)]);
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(destroyed.begin(), destroyed.end());

    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        println(u, v);
    }
    println((int)destroyed.size());
    println(destroyed);

    return 0;
}
