#include "testlib.h"
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, C
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2500, "M");
    inf.readSpace();
    int C = inf.readInt(0, 1000000000, "C");
    inf.readEoln();

    // Prepare adjacency list for directed graph
    struct Edge {
        int to;
        int cost;
    };
    vector<vector<Edge>> adj(N + 1); // 1-based

    for (int i = 0; i < M; ++i) {
        int from = inf.readInt(1, N, "from");
        inf.readSpace();
        int to = inf.readInt(1, N, "to");
        inf.readSpace();
        int cost = inf.readInt(0, 100000, "cost");
        inf.readEoln();

        adj[from].push_back({to, cost});
    }

    // Check that there is a path from 1 to N (as required by the problem)
    // Use BFS for reachability
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const Edge& e : adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }
    ensuref(visited[N], "There is no path from node 1 to node N=%d", N);

    inf.readEof();
}
