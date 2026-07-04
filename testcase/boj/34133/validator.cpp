#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 300000, "M");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, n, "w");
        inf.readEoln();

        adj[v].push_back(w);
        ++indegree[w];
    }

    // CHECK: The statement says the input is a directed acyclic graph, but it
    // does not state that repeated directed edges are forbidden.
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++visited;

        for (int w : adj[v]) {
            --indegree[w];
            if (indegree[w] == 0) {
                q.push(w);
            }
        }
    }

    ensuref(visited == n, "graph must be acyclic");

    inf.readEof();
}
