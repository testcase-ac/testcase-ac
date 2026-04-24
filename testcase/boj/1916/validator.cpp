#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read number of buses M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Build adjacency list for reachability check
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        // Each bus: u -> v with cost
        int u = inf.readInt(1, N, format("u_%d", i+1).c_str());
        inf.readSpace();
        int v = inf.readInt(1, N, format("v_%d", i+1).c_str());
        inf.readSpace();
        int cost = inf.readInt(0, 99999, format("cost_%d", i+1).c_str());
        inf.readEoln();

        // Add directed edge u -> v for connectivity check
        adj[u].push_back(v);
    }

    // Read query: start A, end B
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    // Check that B is reachable from A
    vector<char> seen(N + 1, false);
    queue<int> q;
    seen[A] = true;
    q.push(A);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (!seen[y]) {
                seen[y] = true;
                q.push(y);
            }
        }
    }
    ensuref(seen[B], "City %d is not reachable from city %d", B, A);

    inf.readEof();
    return 0;
}
