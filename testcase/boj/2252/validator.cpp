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
    vector<vector<int>> adj(N + 1);
    vector<int> indegree(N + 1, 0);

    // Read edges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(A != B,
                "Self-loop detected at edge index %d: (%d -> %d)",
                i, A, B);

        adj[A].push_back(B);
        indegree[B]++;
    }

    // Check for cycles via Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited++;
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    ensuref(visited == N,
            "Graph contains a cycle or unreachable nodes: only %d of %d were ordered",
            visited, N);

    inf.readEof();
    return 0;
}
