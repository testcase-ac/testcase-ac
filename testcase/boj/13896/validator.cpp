#include "testlib.h"
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int MAX_T = 10;
const int MAX_N = 100000;
const int MAX_Q = 50000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    int totalN = 0;
    int totalQ = 0;

    for (int test = 1; test <= T; ++test) {
        setTestCase(test);

        int N = inf.readInt(1, MAX_N, "N");
        inf.readSpace();
        int Q = inf.readInt(1, MAX_Q, "Q");
        inf.readSpace();
        int R = inf.readInt(1, N, "R");
        inf.readEoln();

        totalN += N;
        totalQ += Q;

        // Read edges
        vector<vector<int>> adj(N + 1); // 1-based
        set<pair<int, int>> edges;
        for (int i = 0; i < N - 1; ++i) {
            int A = inf.readInt(1, N, "A");
            inf.readSpace();
            int B = inf.readInt(1, N, "B");
            inf.readEoln();

            ensuref(A != B, "Loop detected at edge %d: (%d, %d)", i + 1, A, B);
            int u = min(A, B), v = max(A, B);
            ensuref(!edges.count({u, v}), "Multiple edge detected at edge %d: (%d, %d)", i + 1, A, B);
            edges.insert({u, v});
            adj[A].push_back(B);
            adj[B].push_back(A);
        }

        // Check that the graph is a tree (connected and acyclic)
        // BFS from node 1
        vector<bool> visited(N + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                    ++cnt;
                }
            }
        }
        ensuref(cnt == N, "Graph is not connected: only %d/%d nodes reachable from node 1", cnt, N);

        // Read queries
        for (int i = 0; i < Q; ++i) {
            int S = inf.readInt(0, 1, "S");
            inf.readSpace();
            int U = inf.readInt(1, N, "U");
            inf.readEoln();
        }
    }

    // No extra lines
    inf.readEof();
}
