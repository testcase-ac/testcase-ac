#include "testlib.h"

#include <limits>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2500, "n");
    inf.readEoln();

    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int low = (i == j ? 0 : 1);
            int high = (i == j ? 0 : 9999999);
            dist[i][j] = inf.readInt(low, high, "d_i_j");
        }
        inf.readEoln();
    }
    inf.readEof();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(dist[i][j] == dist[j][i],
                    "distance matrix is not symmetric at (%d, %d): %d != %d",
                    i + 1, j + 1, dist[i][j], dist[j][i]);
        }
    }

    const int inf_value = numeric_limits<int>::max();
    vector<int> min_edge(n, inf_value), parent(n, -1);
    vector<char> used(n, false);
    min_edge[0] = 0;

    vector<vector<pair<int, int>>> tree(n);
    for (int iter = 0; iter < n; ++iter) {
        int v = -1;
        for (int u = 0; u < n; ++u) {
            if (!used[u] && (v == -1 || min_edge[u] < min_edge[v])) {
                v = u;
            }
        }

        ensuref(v != -1 && min_edge[v] != inf_value, "failed to reconstruct a spanning tree");
        used[v] = true;

        if (parent[v] != -1) {
            int w = dist[v][parent[v]];
            tree[v].push_back({parent[v], w});
            tree[parent[v]].push_back({v, w});
        }

        for (int to = 0; to < n; ++to) {
            if (!used[to] && dist[v][to] < min_edge[to]) {
                min_edge[to] = dist[v][to];
                parent[to] = v;
            }
        }
    }

    vector<long long> tree_dist(n);
    vector<pair<int, int>> stack;
    for (int root = 0; root < n; ++root) {
        stack.clear();
        stack.push_back({root, -1});
        tree_dist[root] = 0;

        while (!stack.empty()) {
            auto [v, p] = stack.back();
            stack.pop_back();

            ensuref(tree_dist[v] == dist[root][v],
                    "matrix is not the distance table of its reconstructed tree at (%d, %d): %lld != %d",
                    root + 1, v + 1, tree_dist[v], dist[root][v]);

            for (auto [to, w] : tree[v]) {
                if (to == p) {
                    continue;
                }
                tree_dist[to] = tree_dist[v] + w;
                stack.push_back({to, v});
            }
        }
    }
}
