#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> headerCount(n + 1);
    vector<int> degree(n + 1);
    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> directedEdges;
    set<pair<int, int>> undirectedEdges;

    for (int line = 1; line <= n; ++line) {
        int v = inf.readInt(1, n, "v");
        ++headerCount[v];
        ensuref(headerCount[v] == 1, "vertex %d appears as a header more than once", v);

        set<int> neighborsOnLine;
        while (true) {
            inf.readSpace();
            int to = inf.readInt(-1, n, "neighbor_or_sentinel");
            if (to == -1) {
                break;
            }

            ensuref(to != 0, "neighbor 0 is outside the valid vertex range");
            ensuref(to != v, "self-loop listed for vertex %d", v);
            ensuref(neighborsOnLine.insert(to).second,
                    "duplicate neighbor %d on the adjacency line for vertex %d", to, v);

            directedEdges.insert({v, to});
            undirectedEdges.insert(minmax(v, to));
            graph[v].push_back(to);
            ++degree[v];
        }
        inf.readEoln();
    }

    for (int v = 1; v <= n; ++v) {
        ensuref(headerCount[v] == 1, "vertex %d is missing from adjacency headers", v);
        ensuref(degree[v] > 0, "vertex %d has no listed neighbors", v);
    }

    ensuref((int)directedEdges.size() == 2 * (n - 1),
            "total listed directed edge count is %d, expected %d",
            (int)directedEdges.size(), 2 * (n - 1));
    ensuref((int)undirectedEdges.size() == n - 1,
            "undirected edge count is %d, expected %d",
            (int)undirectedEdges.size(), n - 1);

    for (auto [v, to] : directedEdges) {
        ensuref(directedEdges.count({to, v}) == 1,
                "edge %d -> %d is missing its reverse listing", v, to);
    }

    vector<int> visited(n + 1);
    queue<int> q;
    visited[1] = 1;
    q.push(1);
    int visitedCount = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++visitedCount;
        for (int to : graph[v]) {
            if (!visited[to]) {
                visited[to] = 1;
                q.push(to);
            }
        }
    }
    ensuref(visitedCount == n, "graph is not connected; visited %d of %d vertices", visitedCount, n);

    int s = inf.readInt(1, n, "s");
    (void)s;
    inf.readEoln();
    inf.readEof();
}
