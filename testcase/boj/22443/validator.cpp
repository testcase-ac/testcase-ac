#include "testlib.h"

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    ensuref(s != t, "s and t must be distinct: %d", s);

    vector<vector<int>> graph(n + 1);
    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(m) * 2 + 1);

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        // CHECK: The statement gives an undirected graph, interpreted as simple.
        ensuref(x != y, "loop at edge %d: (%d, %d)", i, x, y);
        int a = min(x, y);
        int b = max(x, y);
        long long key = 1LL * a * (n + 1) + b;
        // CHECK: The statement gives an undirected graph, interpreted as having no multi-edges.
        ensuref(seen.insert(key).second, "duplicate edge at edge %d: (%d, %d)", i, x, y);

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<char> visited(n + 1, 0);
    queue<int> q;
    visited[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (visited[v]) {
                continue;
            }
            visited[v] = 1;
            q.push(v);
        }
    }

    ensuref(visited[t], "t=%d must be reachable from s=%d", t, s);

    inf.readEof();
}
