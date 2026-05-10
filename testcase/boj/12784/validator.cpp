#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        // Read N and M
        int N = inf.readInt(1, 1000, "N");
        inf.readSpace();
        // M should be exactly N-1 for a tree, but we first read in a safe range
        int maxEdges = N * (N - 1) / 2;
        int M = inf.readInt(0, maxEdges, "M");
        inf.readEoln();

        // Enforce tree structure: minimal bridges => M = N-1
        ensuref(M == N - 1,
                "Test case %d: M must be N-1 for a tree, but got N=%d, M=%d",
                tc, N, M);

        // Read edges, check loops and duplicates, build adjacency
        vector<vector<int>> adj(N + 1);
        set<pair<int,int>> seen;
        for (int i = 0; i < M; ++i) {
            int u = inf.readInt(1, N, "u");
            inf.readSpace();
            int v = inf.readInt(1, N, "v");
            inf.readSpace();
            int d = inf.readInt(1, 20, "D");
            inf.readEoln();

            // No loops
            ensuref(u != v,
                    "Test case %d, edge %d: loop detected at (%d, %d)",
                    tc, i+1, u, v);
            // No multiple edges
            int a = min(u, v), b = max(u, v);
            ensuref(!seen.count({a, b}),
                    "Test case %d, edge %d: multiple edges detected between (%d, %d)",
                    tc, i+1, u, v);
            seen.insert({a, b});

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check connectivity from node 1
        vector<char> vis(N + 1, false);
        vector<int> stack;
        stack.reserve(N);
        vis[1] = true;
        stack.push_back(1);
        int cnt = 1;
        while (!stack.empty()) {
            int x = stack.back();
            stack.pop_back();
            for (int y : adj[x]) {
                if (!vis[y]) {
                    vis[y] = true;
                    ++cnt;
                    stack.push_back(y);
                }
            }
        }
        ensuref(cnt == N,
                "Test case %d: graph is not connected, reachable from 1 = %d, expected %d",
                tc, cnt, N);
    }

    inf.readEof();
    return 0;
}
