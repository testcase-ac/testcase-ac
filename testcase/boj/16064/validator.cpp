#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int t = inf.readInt(1, n, "t");
        inf.readSpace();
        inf.readInt(1, 100, "c");
        inf.readEoln();

        graph[s].push_back(t);
        ++indegree[t];
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

        for (int to : graph[v]) {
            --indegree[to];
            if (indegree[to] == 0) {
                q.push(to);
            }
        }
    }

    ensuref(visited == n, "slopes must form a directed acyclic graph");

    inf.readEof();
}
