#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read number of topics
    int n = inf.readInt(1, 400000, "n");
    inf.readEoln();

    // Prepare for dependency sum check and graph representation
    long long sum_d = 0;
    vector<int> indegree(n+1, 0);
    vector<vector<int>> adj(n+1);

    // Read each topic's data
    for (int i = 1; i <= n; i++) {
        // Read e_i and d_i
        int e_i = inf.readInt(1, 1000000, "e_i");
        inf.readSpace();
        int d_i = inf.readInt(0, n-1, "d_i");
        sum_d += d_i;
        ensuref(sum_d <= 400000, "Sum of all d_i exceeds 400000 (got %lld)", sum_d);

        // Read the list of dependencies
        vector<int> deps;
        deps.reserve(d_i);
        for (int j = 0; j < d_i; j++) {
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i_j");
            ensuref(b != i, "Self dependency at topic %d: %d", i, b);
            deps.push_back(b);
        }
        inf.readEoln();

        // Check for duplicates in deps
        if (d_i > 1) {
            sort(deps.begin(), deps.end());
            for (int j = 1; j < d_i; j++) {
                ensuref(deps[j] != deps[j-1],
                        "Duplicate dependency for topic %d: %d", i, deps[j]);
            }
        }

        // Build graph edges: b -> i
        for (int b : deps) {
            adj[b].push_back(i);
            indegree[i]++;
        }
    }

    // Check acyclicity by Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
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
    ensuref(visited == n, "Cycle detected: graph is not a DAG");

    // No extra content
    inf.readEof();
    return 0;
}
