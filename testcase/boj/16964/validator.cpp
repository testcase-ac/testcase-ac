#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: (%d, %d)", i, u, v);

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> order = inf.readInts(n, 1, n, "order_i");
    inf.readEoln();

    vector<char> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[order[i]], "duplicate vertex in DFS order at position %d: %d", i + 1, order[i]);
        seen[order[i]] = true;
    }

    vector<char> visited(n + 1, false);
    queue<int> q;
    visited[1] = true;
    q.push(1);
    int visited_count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ++visited_count;

        for (int next : graph[node]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    ensuref(visited_count == n, "edges do not form a connected tree");

    inf.readEof();
}
