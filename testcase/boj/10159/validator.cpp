#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100, "N");
    inf.readEoln();

    int m = inf.readInt(0, 2000, "M");
    inf.readEoln();

    vector<vector<int>> heavier_than(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "self-comparison at comparison %d: %d %d", i + 1, u, v);
        heavier_than[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited++;
        for (int v : heavier_than[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    ensuref(visited == n, "comparison results are contradictory");

    inf.readEof();
}
