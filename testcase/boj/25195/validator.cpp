#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d -> %d", i, u, v);
        ensuref(edges.insert({u, v}).second, "duplicate edge at edge %d: %d -> %d", i, u, v);

        graph[u].push_back(v);
        ++indegree[v];
    }

    int s = inf.readInt(1, n, "s");
    inf.readEoln();

    set<int> fanclub;
    for (int i = 1; i <= s; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int vertex = inf.readInt(1, n, "fanclub_vertex");
        ensuref(fanclub.insert(vertex).second, "duplicate fanclub vertex at index %d: %d", i, vertex);
    }
    inf.readEoln();
    inf.readEof();

    queue<int> q;
    for (int vertex = 1; vertex <= n; ++vertex) {
        if (indegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++visited;
        for (int next : graph[cur]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    ensuref(visited == n, "graph must be acyclic");
}
