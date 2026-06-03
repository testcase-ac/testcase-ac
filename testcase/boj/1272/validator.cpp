#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int root = inf.readInt(1, n, "root");
    inf.readEoln();

    vector<int> weight(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        weight[i] = inf.readInt(1, 50000, "w_i");
    }
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d", i, u);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u, v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order = {root};
    parent[root] = -1;
    for (int i = 0; i < (int)order.size(); ++i) {
        int v = order[i];
        for (int u : graph[v]) {
            if (u == parent[v]) {
                continue;
            }
            ensuref(parent[u] == 0, "cycle detected involving node %d", u);
            parent[u] = v;
            order.push_back(u);
        }
    }

    ensuref((int)order.size() == n, "tree is not connected from root %d", root);
    for (int v = 1; v <= n; ++v) {
        if (v == root) {
            continue;
        }
        ensuref(weight[v] > weight[parent[v]],
                "node %d weight %d is not greater than parent %d weight %d",
                v, weight[v], parent[v], weight[parent[v]]);
    }

    inf.readEof();
}
