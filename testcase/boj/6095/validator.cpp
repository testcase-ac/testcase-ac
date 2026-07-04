#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "N");
    inf.readEoln();

    vector<int> degree(n + 1, 0);
    set<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        int v1 = inf.readInt(1, n, "V1");
        inf.readSpace();
        int v2 = inf.readInt(1, n, "V2");
        inf.readEoln();

        // CHECK: The statement describes polygon sides over vertices 1..N.
        ensuref(v1 != v2, "border side %d is a self-loop at vertex %d", i + 1, v1);
        pair<int, int> edge = minmax(v1, v2);
        ensuref(edges.insert(edge).second,
                "duplicate border side %d between vertices %d and %d", i + 1, edge.first,
                edge.second);
        ++degree[v1];
        ++degree[v2];
    }

    for (int v = 1; v <= n; ++v) {
        // CHECK: Assembling all listed sides into polygon islands requires every vertex
        // to have exactly two incident border sides.
        ensuref(degree[v] == 2, "vertex %d has degree %d, expected 2", v, degree[v]);
    }

    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            cost[i][j] = inf.readInt(0, 1000, "cost");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(cost[i][j] == cost[j][i],
                    "cost matrix is not symmetric at (%d, %d): %d != %d", i + 1, j + 1,
                    cost[i][j], cost[j][i]);
        }
    }

    inf.readEof();
}
