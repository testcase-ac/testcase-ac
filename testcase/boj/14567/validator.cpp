#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 500000, "M");
    inf.readEoln();

    // Prepare adjacency list and indegree for cycle check
    vector<vector<int>> adj(N + 1); // 1-based indexing
    vector<int> indeg(N + 1, 0);
    set<pair<int, int>> prereq_edges;

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();

        ensuref(A < B, "Prerequisite edge %d: A (%d) must be less than B (%d)", i + 1, A, B);

        ensuref(prereq_edges.count({A, B}) == 0, "Duplicate prerequisite edge at line %d: (%d, %d)", i + 2, A, B);
        prereq_edges.insert({A, B});

        adj[A].push_back(B);
        indeg[B]++;
    }

    // Check for cycles using Kahn's algorithm (topological sort)
    queue<int> q;
    int processed = 0;
    for (int i = 1; i <= N; ++i) {
        if (indeg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        processed++;
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    ensuref(processed == N, "The prerequisite graph contains a cycle or is not a DAG (only %d/%d nodes processed)", processed, N);

    inf.readEof();
}
