#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of buildings
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Adjacency list: edge u->v if u must be built before v
    vector<vector<int>> adj(N);

    for (int i = 1; i <= N; i++) {
        // Build time for building i
        inf.readInt(1, 100000, "t_i");
        // Read dependencies until -1
        while (true) {
            inf.readSpace();
            int d = inf.readInt(-1, N, "dep");
            if (d == -1) {
                break;
            }
            // No self-dependency
            ensuref(d != i,
                    "Building %d has self-dependency on %d", i, d);
            // Record edge from dependency d to i
            adj[d - 1].push_back(i - 1);
        }
        inf.readEoln();
    }

    // Check the dependency graph is acyclic (so all buildings can be built)
    vector<int> indeg(N, 0);
    for (int u = 0; u < N; u++) {
        for (int v : adj[u]) {
            indeg[v]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    int countVisited = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        countVisited++;
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(countVisited == N,
            "Dependency graph has a cycle; not all buildings can be built");

    inf.readEof();
    return 0;
}
