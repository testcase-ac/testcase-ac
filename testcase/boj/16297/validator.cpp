#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(0LL, 1000000000LL, "c_i");
    }
    inf.readEoln();

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    set<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int s = inf.readInt(0, n - 1, "s");
        inf.readSpace();
        int t = inf.readInt(0, n - 1, "t");
        inf.readEoln();

        ensuref(edges.insert({s, t}).second,
                "duplicate edge at index %d: %d -> %d", i + 1, s, t);
        graph[s].push_back(t);
        ++indegree[t];
    }

    vector<char> reachable(n, false);
    queue<int> bfs;
    reachable[0] = true;
    bfs.push(0);
    while (!bfs.empty()) {
        int v = bfs.front();
        bfs.pop();
        for (int to : graph[v]) {
            if (!reachable[to]) {
                reachable[to] = true;
                bfs.push(to);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        ensuref(reachable[i], "stall %d is not reachable from stall 0", i);
    }

    queue<int> ready;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            ready.push(i);
        }
    }

    int visited = 0;
    while (!ready.empty()) {
        int v = ready.front();
        ready.pop();
        ++visited;
        for (int to : graph[v]) {
            --indegree[to];
            if (indegree[to] == 0) {
                ready.push(to);
            }
        }
    }
    ensuref(visited == n, "the directed graph must be acyclic");

    inf.readEof();
}
