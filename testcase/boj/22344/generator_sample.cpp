#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int w) {
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) edges.push_back({u, v, w});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 14);
    if (mode == 2) n = rnd.next(3, 13) | 1;
    if (mode == 3) n = rnd.next(4, 14);

    vector<int> x(n + 1);
    int valueLimit = rnd.next(0, 1) ? 20 : 100000;
    for (int i = 1; i <= n; ++i) x[i] = rnd.next(-valueLimit, valueLimit);

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, x[i] + x[i + 1]);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            int p = rnd.next(1, i - 1);
            addEdge(edges, used, p, i, x[p] + x[i]);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            int j = i == n ? 1 : i + 1;
            addEdge(edges, used, i, j, x[i] + x[j]);
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            int j = i == n ? 1 : i + 1;
            addEdge(edges, used, i, j, x[i] + x[j]);
        }
        int bad = rnd.next((int)edges.size());
        int delta = rnd.next(0, 1) ? 1 : -1;
        edges[bad].w += delta;
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            int p = rnd.next(1, i - 1);
            addEdge(edges, used, p, i, x[p] + x[i]);
        }
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (!used.count({i, j})) candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = candidates.empty() ? 0 : rnd.next(1, min((int)candidates.size(), n));
        for (int i = 0; i < extra; ++i) {
            auto [u, v] = candidates[i];
            addEdge(edges, used, u, v, x[u] + x[v]);
        }
    } else {
        int left = rnd.next(1, n - 1);
        int hub = left + 1;
        for (int u = 1; u <= left; ++u) {
            addEdge(edges, used, u, hub, x[u] + x[hub]);
        }
        for (int v = hub + 1; v <= n; ++v) {
            int u = rnd.next(1, left);
            addEdge(edges, used, u, v, x[u] + x[v]);
        }
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= left; ++u) {
            for (int v = left + 1; v <= n; ++v) {
                if (!used.count({u, v})) candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = candidates.empty() ? 0 : rnd.next(0, min((int)candidates.size(), n));
        for (int i = 0; i < extra; ++i) {
            auto [u, v] = candidates[i];
            addEdge(edges, used, u, v, x[u] + x[v]);
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.u, edge.v);
    }

    println(n, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
