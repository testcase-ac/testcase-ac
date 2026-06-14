#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(10, 14);
    int p = rnd.next(3, min(6, n - 3));
    int x = 1;
    int z = n;

    vector<int> intermediates;
    for (int i = 2; i < 2 + p; ++i) {
        intermediates.push_back(i);
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    auto addEdge = [&](int u, int v, int w) {
        if (u == v) {
            return;
        }
        if (u > v) {
            swap(u, v);
        }
        if (used.insert({u, v}).second) {
            edges.push_back({u, v, w});
        }
    };

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 20));
        }
        addEdge(x, z, rnd.next(50, 200));
    } else if (mode == 1) {
        for (int y : intermediates) {
            addEdge(x, y, rnd.next(1, 30));
            addEdge(y, z, rnd.next(1, 30));
        }
        for (int i = 0; i + 1 < (int)intermediates.size(); ++i) {
            addEdge(intermediates[i], intermediates[i + 1], rnd.next(1, 10));
        }
    } else if (mode == 2) {
        int split = rnd.next(5, n - 3);
        for (int i = 1; i < split; ++i) {
            addEdge(i, i + 1, rnd.next(1, 40));
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 40));
        }
    } else {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 100));
        }
        for (int i = 0; i < p; ++i) {
            for (int j = i + 1; j < p; ++j) {
                if (rnd.next(0, 1)) {
                    addEdge(intermediates[i], intermediates[j], rnd.next(1, 25));
                }
            }
        }
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxEdges = min((int)candidates.size() + (int)edges.size(), rnd.next(10, min(32, n * (n - 1) / 2)));
    for (auto [u, v] : candidates) {
        if ((int)edges.size() >= maxEdges) {
            break;
        }
        int w;
        int weightMode = rnd.next(0, 3);
        if (weightMode == 0) {
            w = 1;
        } else if (weightMode == 1) {
            w = rnd.next(2, 30);
        } else if (weightMode == 2) {
            w = rnd.next(100, 1000);
        } else {
            w = rnd.next(500000, 1000000);
        }
        addEdge(u, v, w);
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

    shuffle(edges.begin(), edges.end());
    shuffle(intermediates.begin(), intermediates.end());

    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        int u = label[edge.u];
        int v = label[edge.v];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v, edge.w);
    }
    println(label[x], label[z]);
    println(p);

    vector<int> ys;
    for (int y : intermediates) {
        ys.push_back(label[y]);
    }
    println(ys);

    return 0;
}
