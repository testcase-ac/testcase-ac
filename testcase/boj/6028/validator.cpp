#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 100000, "M");
    inf.readSpace();
    int b = inf.readInt(1, 25000, "B");
    inf.readEoln();

    ensuref(2 * b <= n, "2 * B must be at most N, got B=%d and N=%d", b, n);

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int r = inf.readInt(1, n, "R_i");
        inf.readSpace();
        int s = inf.readInt(1, n, "S_i");
        inf.readSpace();
        inf.readInt(1, 2000, "L_i");
        inf.readEoln();

        // CHECK: The statement explicitly allows parallel paths, but does not
        // say whether a path may connect a pasture to itself.
        graph[r].push_back(s);
        graph[s].push_back(r);
    }

    vector<int> occupied(n + 1, 0);
    for (int i = 0; i < b; ++i) {
        int p = inf.readInt(1, n, "P_i");
        inf.readSpace();
        int q = inf.readInt(1, n, "Q_i");
        inf.readEoln();

        ensuref(!occupied[p], "bull pasture at query %d is not unique: %d", i + 1, p);
        occupied[p] = 1;
        ensuref(!occupied[q], "cow pasture at query %d is not unique: %d", i + 1, q);
        occupied[q] = 1;
    }

    vector<int> seen(n + 1, 0);
    queue<int> q;
    q.push(1);
    seen[1] = 1;
    int reached = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                q.push(to);
                ++reached;
            }
        }
    }
    ensuref(reached == n, "barn reaches only %d of %d pastures", reached, n);

    inf.readEof();
}
