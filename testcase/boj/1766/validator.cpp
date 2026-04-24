#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 32000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Prepare adjacency list and indegree array
    vector<vector<int>> adj(N+1);
    vector<int> indeg(N+1, 0);

    // Read edges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();
        // No self-dependency
        ensuref(A != B,
                "Self dependency detected at edge %d: %d -> %d", i+1, A, B);
        adj[A].push_back(B);
        indeg[B]++;
    }

    // Check DAG (no cycles) via Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(cnt == N, "Cycle detected: graph is not a DAG");

    // The input must end here
    inf.readEof();
    return 0;
}
