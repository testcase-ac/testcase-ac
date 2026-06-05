#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n - 1, "M");
    inf.readEoln();

    vector<int> company(n);
    for (int i = 0; i < n; ++i) {
        company[i] = inf.readInt(0, 1, "C_i");
        inf.readEoln();
    }

    vector<vector<int>> edge(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            edge[i][j] = inf.readInt(0, 1000, "E_ij");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        // CHECK: The statement describes connections between subway stations, so self-connections are not valid routes.
        ensuref(edge[i][i] == 0, "E_%d%d must be 0", i, i);
        for (int j = i + 1; j < n; ++j) {
            // CHECK: The statement describes whether station i and station j are connected, which defines an undirected matrix.
            ensuref(edge[i][j] == edge[j][i],
                    "connection matrix must be symmetric at (%d, %d): %d != %d",
                    i,
                    j,
                    edge[i][j],
                    edge[j][i]);
        }
    }

    vector<int> seen(n);
    queue<int> q;
    seen[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (edge[u][v] > 0 && !seen[v]) {
                seen[v] = 1;
                q.push(v);
            }
        }
    }
    ensuref(seen[m], "destination %d is not reachable from station 0", m);

    inf.readEof();
}
