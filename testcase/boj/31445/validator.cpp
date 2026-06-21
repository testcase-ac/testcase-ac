#include "testlib.h"

#include <queue>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);
    set<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(x != y, "self relation at edge index %d: (%d, %d)", i + 1, x, y);
        ensuref(edges.insert({x, y}).second,
                "duplicate relation at edge index %d: (%d, %d)", i + 1, x, y);

        graph[x].push_back(y);
        ++indegree[y];
    }

    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (indegree[v] == 0) {
            q.push(v);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++visited;

        for (int next : graph[v]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    ensuref(visited == n, "relations must be non-contradictory and acyclic");

    inf.readEof();
}
