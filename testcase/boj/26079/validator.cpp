#include "testlib.h"

#include <queue>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n - 1, "M");
    inf.readEoln();

    vector<int> indegree(n + 1, 0);
    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d -> %d", i, a, b);
        ensuref(edges.insert({a, b}).second,
                "duplicate edge at edge %d: %d -> %d", i, a, b);

        ++indegree[b];
        ensuref(indegree[b] <= 1,
                "lecture %d has more than one prerequisite at edge %d", b, i);
        graph[a].push_back(b);
    }

    queue<int> q;
    vector<int> remainingIndegree = indegree;
    for (int v = 1; v <= n; ++v) {
        if (remainingIndegree[v] == 0) {
            q.push(v);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++visited;

        for (int to : graph[v]) {
            --remainingIndegree[to];
            if (remainingIndegree[to] == 0) {
                q.push(to);
            }
        }
    }

    ensuref(visited == n, "lecture dependency graph contains a cycle");

    inf.readEof();
}
