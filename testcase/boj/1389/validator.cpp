#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of users N and number of friendships M
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 5000, "M");
    inf.readEoln();

    // Adjacency list to check degree and connectivity
    vector<vector<int>> adj(N + 1);

    // Read friendship relations
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(a != b,
                "Loop detected at friendship index %d: (%d, %d)",
                i, a, b);

        // record edges (duplicates allowed)
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Ensure every person has at least one friend
    for (int i = 1; i <= N; i++) {
        ensuref(!adj[i].empty(),
                "Person %d has no friends", i);
    }

    // Check graph connectivity via BFS from node 1
    vector<bool> vis(N + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int visited_count = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                visited_count++;
                q.push(v);
            }
        }
    }
    ensuref(visited_count == N,
            "Graph is disconnected: only %d out of %d reachable from node 1",
            visited_count, N);

    inf.readEof();
    return 0;
}
