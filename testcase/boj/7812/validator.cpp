#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int findSet(vector<int>& parent, int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent, parent[x]);
    return parent[x];
}

bool unionSet(vector<int>& parent, vector<int>& rnk, int x, int y) {
    int rx = findSet(parent, x);
    int ry = findSet(parent, y);
    if (rx == ry) return false;
    if (rnk[rx] < rnk[ry]) 
        parent[rx] = ry;
    else if (rnk[ry] < rnk[rx])
        parent[ry] = rx;
    else {
        parent[ry] = rx;
        rnk[rx]++;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCase = 0;
    while (true) {
        // Read number of vertices or 0 to end
        int n = inf.readInt(0, 10000, "n");
        inf.readEoln();
        if (n == 0) break;
        testCase++;

        // Prepare DSU for connectivity check
        vector<int> parent(n), rnk(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
        int successfulUnions = 0;

        // Track edges to detect loops and multiple edges
        set<pair<int,int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int a = inf.readInt(0, n-1, "a_i");
            inf.readSpace();
            int b = inf.readInt(0, n-1, "b_i");
            inf.readSpace();
            int w = inf.readInt(1, 100,   "w_i");
            inf.readEoln();

            // No loops
            ensuref(a != b,
                    "Loop detected at edge %d in test case %d: (%d, %d)",
                    i, testCase, a, b);

            // No multiple edges
            int u = min(a, b), v = max(a, b);
            ensuref(!edges.count({u, v}),
                    "Multiple edges detected at edge %d in test case %d: (%d, %d)",
                    i, testCase, a, b);
            edges.insert({u, v});

            // Build DSU and detect cycles
            bool merged = unionSet(parent, rnk, u, v);
            ensuref(merged,
                    "Cycle detected at edge %d in test case %d: (%d, %d)",
                    i, testCase, a, b);
            successfulUnions++;
        }

        // Check connectivity: for a tree with n>1, we must have exactly n-1 successful unions
        if (n > 1) {
            ensuref(successfulUnions == n - 1,
                    "Graph is not connected in test case %d: only %d unions out of %d edges",
                    testCase, successfulUnions, n-1);
        }
    }

    inf.readEof();
    return 0;
}
