#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(3, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(3, 4000, "M");
    inf.readEoln();

    // 2. Read M roads: x_j, y_j, t_j
    set<pair<int, int>> edge_set;
    vector<vector<pair<int, int>>> adj(N + 1); // 1-based
    for (int j = 1; j <= M; ++j) {
        int x_j = inf.readInt(1, N, "x_j");
        inf.readSpace();
        int y_j = inf.readInt(1, N, "y_j");
        inf.readSpace();
        int t_j = inf.readInt(1, 100000, "t_j");
        inf.readEoln();

        ensuref(x_j != y_j, "Self-loop detected at road %d: (%d, %d)", j, x_j, y_j);
        ensuref(!edge_set.count({x_j, y_j}), "Multiple edges detected at road %d: (%d, %d)", j, x_j, y_j);
        edge_set.insert({x_j, y_j});
        adj[x_j].emplace_back(y_j, t_j);
    }

    // 3. Read c_1..c_N
    vector<int> c(N + 1); // 1-based
    for (int i = 1; i <= N; ++i) {
        c[i] = inf.readInt(0, 1, "c_i");
        if (i < N) inf.readSpace();
    }
    inf.readEoln();

    ensuref(c[1] == 0, "c_1 must be 0, but got %d", c[1]);
    ensuref(c[N] == 0, "c_N must be 0, but got %d", c[N]);

    // 4. Read a, b
    int a = inf.readInt(1, 1000000000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 1000000000, "b");
    inf.readEoln();

    // 5. Check that the graph is not degenerate: at least one path from 1 to N
    //    (Otherwise, the answer is always -1, which is not guaranteed by the statement)
    //    So, check reachability from 1 to N
    vector<bool> vis(N + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : adj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    ensuref(vis[N], "There is no path from building 1 to building N");

    inf.readEof();
}
