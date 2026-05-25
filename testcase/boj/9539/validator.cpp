#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MIN = 1, T_MAX = 100000;
    const int N_MIN = 2, N_MAX = 200000;
    const int HP_MIN = -1000000, HP_MAX = 1000000;
    const long long TOTAL_N_MAX = 1600000; // CHECK: practical input-size cap.

    int T = inf.readInt(T_MIN, T_MAX, "T");
    inf.readEoln();

    long long total_n = 0;
    for (int test = 0; test < T; ++test) {
        setTestCase(test+1);

        // Read n and t
        int n = inf.readInt(N_MIN, N_MAX, "n");
        inf.readSpace();
        int t = inf.readInt(2, n, "t");
        inf.readEoln();

        total_n += n;
        ensuref(total_n <= TOTAL_N_MAX, "total n exceeds practical limit at test case %d", test+1);

        // Read HP values
        vector<int> hp(n+1); // 1-based
        for (int i = 1; i <= n; ++i) {
            hp[i] = inf.readInt(HP_MIN, HP_MAX, "hp_i");
            if (i < n) inf.readSpace();
        }
        inf.readEoln();

        // The first chamber does not contain a monster
        ensuref(hp[1] >= 0, "First chamber (1) must not contain a monster (hp[1] >= 0), got %d", hp[1]);

        // Read corridors and build adjacency list
        vector<vector<int>> adj(n+1);
        set<pair<int,int>> edges;
        for (int i = 0; i < n-1; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a != b, "Self-loop detected at corridor %d: (%d, %d)", i+1, a, b);
            int u = min(a, b), v = max(a, b);
            ensuref(!edges.count({u, v}), "Multiple edge detected at corridor %d: (%d, %d)", i+1, a, b);
            edges.insert({u, v});

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // Check that the graph is connected (all chambers reachable from 1)
        vector<bool> vis(n+1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                    ++cnt;
                }
            }
        }
        ensuref(cnt == n, "Dungeon is not connected: only %d/%d chambers reachable from 1", cnt, n);

        // Check that the graph is a tree (n-1 edges, already checked for multiple edges and self-loops)
        // No further check needed.

        // No further global properties to check (the rest is for the solution).

    }

    inf.readEof();
}
