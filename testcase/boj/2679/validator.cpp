#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read N, E, A, B
        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        // No explicit upper bound for E in problem; we cap it by 1e6 to avoid absurd sizes
        int E = inf.readInt(1, 1000000, "E");
        inf.readSpace();
        int A = inf.readInt(0, N - 1, "A");
        inf.readSpace();
        int B = inf.readInt(0, N - 1, "B");
        inf.readEoln();

        ensuref(A != B, "In test case %d, A (%d) must not equal B (%d)", tc, A, B);

        // Build adjacency for reachability check
        vector<vector<int>> adj(N);
        for (int i = 0; i < E; i++) {
            int U = inf.readInt(0, N - 1, "U");
            inf.readSpace();
            int V = inf.readInt(0, N - 1, "V");
            inf.readSpace();
            int W = inf.readInt(1, 1000, "W");
            inf.readEoln();

            ensuref(U != V,
                    "Loop detected at edge index %d in test case %d: (%d -> %d)",
                    i, tc, U, V);

            // Record edge for reachability
            adj[U].push_back(V);
        }

        // Check that B is reachable from A
        vector<char> vis(N, 0);
        queue<int> q;
        vis[A] = 1;
        q.push(A);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        ensuref(vis[B],
                "In test case %d, node B (%d) is not reachable from A (%d)",
                tc, B, A);
    }

    inf.readEof();
    return 0;
}
