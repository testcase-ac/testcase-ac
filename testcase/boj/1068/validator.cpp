#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read parent list
    vector<int> parent = inf.readInts(n, -1, n-1, "parent");
    inf.readEoln();

    // Read the node to delete
    int del = inf.readInt(0, n-1, "del");
    inf.readEoln();

    // Validate exactly one root and no self-parenting
    int rootCount = 0, rootIndex = -1;
    for (int i = 0; i < n; i++) {
        if (parent[i] == -1) {
            rootCount++;
            rootIndex = i;
        } else {
            ensuref(parent[i] != i,
                    "Node %d has itself as parent", i);
        }
    }
    ensuref(rootCount == 1,
            "There must be exactly one root, found %d", rootCount);

    // Check for connectivity and absence of cycles:
    // Every node must reach the single root by following parent links,
    // and we must not encounter a cycle on the way.
    for (int i = 0; i < n; i++) {
        vector<bool> seen(n, false);
        int cur = i;
        while (parent[cur] != -1) {
            // parent[cur] is in range by readInts, but double-check
            ensuref(parent[cur] >= 0 && parent[cur] < n,
                    "Invalid parent %d for node %d", parent[cur], cur);
            ensuref(!seen[cur],
                    "Cycle detected when tracing from node %d", i);
            seen[cur] = true;
            cur = parent[cur];
        }
        ensuref(cur == rootIndex,
                "Node %d is not connected to the root %d", i, rootIndex);
    }

    inf.readEof();
    return 0;
}
