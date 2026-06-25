#include "testlib.h"

#include <queue>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says N <= 15; N is the number of cities, so
    // the validator requires at least one city.
    int n = inf.readInt(1, 15, "N");
    inf.readEoln();

    vector<string> adj(n);
    for (int i = 0; i < n; ++i) {
        adj[i] = inf.readLine("[01]{1,15}", "adjacency row");
        ensuref((int)adj[i].size() == n,
                "row %d has length %d, expected %d",
                i + 1,
                (int)adj[i].size(),
                n);
        ensuref(adj[i][i] == '0', "diagonal entry (%d, %d) must be 0", i + 1, i + 1);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(adj[i][j] == adj[j][i],
                    "matrix is not symmetric at (%d, %d) and (%d, %d)",
                    i + 1,
                    j + 1,
                    j + 1,
                    i + 1);
        }
    }

    vector<int> seen(n);
    queue<int> q;
    seen[0] = 1;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to = 0; to < n; ++to) {
            if (adj[v][to] == '1' && !seen[to]) {
                seen[to] = 1;
                q.push(to);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        ensuref(seen[i], "city %d is not reachable from city 1", i + 1);
    }

    inf.readEof();
}
