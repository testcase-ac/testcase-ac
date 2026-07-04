#include "testlib.h"

#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    int trueCount = 0;
    for (int i = 1; i <= n; ++i) {
        inf.readToken("set|unset", "type");
        inf.readSpace();
        string result = inf.readToken("true|false", "result");
        inf.readEoln();
        if (result == "true") {
            ++trueCount;
        }
    }
    ensuref(trueCount <= 2, "more than two operations have true results: %d", trueCount);

    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "loop at arc index %d: %d -> %d", i, a, b);
        // CHECK: The statement describes arcs of a DAG; validate them as a graph edge set.
        ensuref(edges.insert({a, b}).second, "duplicate arc at index %d: %d -> %d", i, a, b);
        graph[a].push_back(b);
        ++indegree[b];
    }

    queue<int> ready;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            ready.push(i);
        }
    }

    int visited = 0;
    while (!ready.empty()) {
        int node = ready.front();
        ready.pop();
        ++visited;

        for (int next : graph[node]) {
            --indegree[next];
            if (indegree[next] == 0) {
                ready.push(next);
            }
        }
    }
    ensuref(visited == n, "arcs do not form a DAG");

    inf.readEof();
}
