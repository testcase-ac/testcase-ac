#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        inf.readInt(1, 1000, "L_i");
        inf.readEoln();

        ensuref(a != b, "edge %d has the same endpoint %d", i, a);
        ensuref(edges.insert({min(a, b), max(a, b)}).second,
                "duplicate edge %d between %d and %d", i, a, b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> seen(n + 1, 0);
    queue<int> bfs;
    seen[1] = 1;
    bfs.push(1);
    int reachable = 0;
    while (!bfs.empty()) {
        int city = bfs.front();
        bfs.pop();
        ++reachable;
        for (int next : graph[city]) {
            if (seen[next]) {
                continue;
            }
            seen[next] = 1;
            bfs.push(next);
        }
    }
    ensuref(reachable == n, "graph is not connected: reached %d of %d cities", reachable, n);

    vector<int> hasFestival(n + 1, 0);
    for (int i = 1; i <= k; ++i) {
        int city = inf.readInt(1, n, "F_i");
        inf.readEoln();
        ensuref(!hasFestival[city], "duplicate festival city %d", city);
        hasFestival[city] = 1;
    }

    for (int i = 1; i <= q; ++i) {
        int s = inf.readInt(1, n, "S_i");
        inf.readSpace();
        int t = inf.readInt(1, n, "T_i");
        inf.readEoln();
        ensuref(s != t, "query %d has equal start and target city %d", i, s);
    }

    inf.readEof();
}
