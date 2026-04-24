#include "testlib.h"
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read number of wheels
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        vector<int> x(n), y(n), r(n);
        for (int i = 0; i < n; i++) {
            x[i] = inf.readInt(-10000, 10000, "x");
            inf.readSpace();
            y[i] = inf.readInt(-10000, 10000, "y");
            inf.readSpace();
            r[i] = inf.readInt(1, 10000, "r");
            inf.readEoln();
        }

        // Check no overlapping wheels and build touching graph
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long dx = x[i] - x[j];
                long long dy = y[i] - y[j];
                long long d2 = dx*dx + dy*dy;
                long long sr = (long long)r[i] + r[j];
                long long sr2 = sr * sr;
                // No interior overlap: distance^2 >= (ri + rj)^2
                ensuref(d2 >= sr2,
                        "Testcase %d: wheels %d and %d overlap (centers=(%d,%d),(%d,%d), radii=%d,%d)",
                        tc, i+1, j+1, x[i], y[i], x[j], y[j], r[i], r[j]);
                // If they touch exactly, add edge
                if (d2 == sr2) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        // Check the touching graph is bipartite (no odd cycle) => machine not jammed
        vector<int> color(n, 0);
        for (int i = 0; i < n; i++) {
            if (color[i] != 0) continue;
            // BFS from i
            queue<int> q;
            color[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] == 0) {
                        color[v] = -color[u];
                        q.push(v);
                    } else {
                        ensuref(color[v] != color[u],
                                "Testcase %d: odd cycle detected touching wheels %d and %d",
                                tc, u+1, v+1);
                    }
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
