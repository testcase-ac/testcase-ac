#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N and K
        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        int K = inf.readInt(1, 100000, "K");
        inf.readEoln();

        // Read build times D_i
        vector<int> D = inf.readInts(N, 0, 100000, "D_i");
        inf.readEoln();

        // Read edges
        vector<pair<int,int>> edges;
        edges.reserve(K);
        for (int i = 0; i < K; ++i) {
            int X = inf.readInt(1, N, "X");
            inf.readSpace();
            int Y = inf.readInt(1, N, "Y");
            inf.readEoln();
            edges.emplace_back(X, Y);
        }

        // Read target W
        int W = inf.readInt(1, N, "W");
        inf.readEoln();

        // Build adjacency list, removing duplicate edges
        sort(edges.begin(), edges.end());
        edges.erase(unique(edges.begin(), edges.end()), edges.end());

        vector<vector<int>> adj(N+1);
        vector<int> indegree(N+1, 0);
        for (auto &e : edges) {
            int x = e.first, y = e.second;
            adj[x].push_back(y);
            indegree[y]++;
        }

        // Check for cycles via Kahn's algorithm
        queue<int> q;
        for (int i = 1; i <= N; ++i) {
            if (indegree[i] == 0) q.push(i);
        }
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cnt++;
            for (int v : adj[u]) {
                --indegree[v];
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        ensuref(cnt == N,
                "Graph contains a cycle in test case %d: only %d of %d nodes were topologically sorted",
                tc, cnt, N);
    }

    inf.readEof();
    return 0;
}
