#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, X
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readEoln();

    // Prepare to detect duplicate edges and build adjacency
    vector<vector<char>> hasEdge(N+1, vector<char>(N+1, 0));
    vector<vector<int>> g(N+1), gr(N+1);

    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int t = inf.readInt(1, 100, "t_i");
        inf.readEoln();

        // No self-loop
        ensuref(a != b,
                "Self-loop detected at edge %d: (%d -> %d)", i+1, a, b);
        // No multi-edge
        ensuref(!hasEdge[a][b],
                "Multiple edges detected from %d to %d at edge %d", a, b, i+1);
        hasEdge[a][b] = 1;

        // Build graph and reverse graph
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    // Check reachability from X to all nodes
    vector<char> vis_from_X(N+1, 0), vis_to_X(N+1, 0);
    queue<int> q;

    // BFS on g from X -> mark vis_from_X
    q.push(X);
    vis_from_X[X] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (!vis_from_X[v]) {
                vis_from_X[v] = 1;
                q.push(v);
            }
        }
    }
    // BFS on reverse graph gr from X -> mark vis_to_X (nodes that can reach X)
    q.push(X);
    vis_to_X[X] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : gr[u]) {
            if (!vis_to_X[v]) {
                vis_to_X[v] = 1;
                q.push(v);
            }
        }
    }

    // Validate global connectivity conditions
    for (int i = 1; i <= N; i++) {
        ensuref(vis_to_X[i],
                "Node %d cannot reach X=%d", i, X);
        ensuref(vis_from_X[i],
                "X=%d cannot reach node %d", X, i);
    }

    // Final formatting checks
    inf.readEof();
    return 0;
}
