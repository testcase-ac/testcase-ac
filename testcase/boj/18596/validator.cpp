#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 2000, "T");
    inf.readEoln();

    long long sumN = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= 1000000, "sum of n over all test cases must be at most 1e6, got %lld", sumN);

        // monsters at intersections 2..n
        // n-1 lines with a_i, b_i
        for (int i = 2; i <= n; ++i) {
            long long a = inf.readLong(0LL, 1000000000LL, "a_i");
            inf.readSpace();
            long long b = inf.readLong(0LL, 1000000000LL, "b_i");
            inf.readEoln();
            (void)a;
            (void)b;
        }

        // read tree edges
        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();
            ensuref(u != v, "self-loop edge is not allowed at test %d, edge %d: (%d,%d)", tc, i + 1, u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // validate that edges form a single tree (connected, no multiple edges)
        // we'll do BFS from node 1 and check connectivity; multi-edges are allowed
        // by statement unless explicitly forbidden, but they would still yield a tree
        // only if there are no cycles, i.e., m = n-1 and graph is connected.
        // So checking connectivity suffices given m = n-1 and no self-loops.
        vector<char> vis(n + 1, 0);
        vector<int> q(n);
        int qs = 0, qe = 0;
        q[qe++] = 1;
        vis[1] = 1;
        while (qs < qe) {
            int v = q[qs++];
            for (int to : g[v]) {
                if (!vis[to]) {
                    vis[to] = 1;
                    q[qe++] = to;
                }
            }
        }
        for (int v = 1; v <= n; ++v) {
            ensuref(vis[v], "graph is not connected in test %d, vertex %d is unreachable from 1", tc, v);
        }
    }

    inf.readEof();
}
