#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInt(1, n, "A");
    inf.readSpace();
    inf.readInt(1, n, "B");
    inf.readSpace();
    inf.readInt(1, n, "C");
    inf.readEoln();

    int m = inf.readInt(n - 1, 500000, "M");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= m; ++i) {
        int d = inf.readInt(1, n, "D");
        inf.readSpace();
        int e = inf.readInt(1, n, "E");
        inf.readSpace();
        inf.readInt(1, 10000, "L");
        inf.readEoln();

        graph[d].push_back(e);
        graph[e].push_back(d);
    }

    vector<char> seen(n + 1, false);
    queue<int> q;
    seen[1] = true;
    q.push(1);

    int reached = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++reached;

        for (int next : graph[cur]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }

    ensuref(reached == n, "graph must be connected, reached %d of %d nodes", reached, n);

    inf.readEof();
}
