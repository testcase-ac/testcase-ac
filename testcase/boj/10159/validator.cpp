#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(5, 100, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(0, 2000, "M");
    inf.readEoln();

    // Read comparisons
    vector<vector<int>> adj(N+1);
    vector<int> indegree(N+1, 0);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Self-comparison detected at line %d: %d %d", 
                i+3, u, v);
        adj[u].push_back(v);
        indegree[v]++;
    }

    // Check for cycles via Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    int visited = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited++;
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    ensuref(visited == N,
            "Input contains a cycle or inconsistency: not a DAG");

    inf.readEof();
    return 0;
}
