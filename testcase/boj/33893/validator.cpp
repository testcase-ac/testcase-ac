#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 16, "N");
    inf.readSpace();
    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(n - 1, maxEdges, "M");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "K");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: %d %d", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> seen(n + 1, false);
    queue<int> q;
    seen[1] = true;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!seen[v]) {
                seen[v] = true;
                q.push(v);
            }
        }
    }
    for (int v = 1; v <= n; ++v) {
        ensuref(seen[v], "graph is disconnected: vertex %d is not reachable from 1", v);
    }

    set<int> defenders;
    for (int j = 1; j <= k; ++j) {
        int p = inf.readInt(2, n, "p_j");
        ensuref(defenders.insert(p).second, "duplicate defender position at index %d: %d", j, p);
        if (j < k) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
