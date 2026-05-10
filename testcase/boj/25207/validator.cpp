#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read array a[1..N]
    vector<long long> a = inf.readLongs(N, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // Prepare parent array: parent[v] = u if u is parent of v
    vector<int> parent(N+1, 0);

    // Read N-1 edges
    for (int i = 0; i < N - 1; i++) {
        int u = inf.readInt(1, N, "parent");
        inf.readSpace();
        int v = inf.readInt(1, N, "child");
        inf.readEoln();

        // No self-loop
        ensuref(u != v,
                "Loop detected at edge %d: parent %d and child %d must differ", i+1, u, v);
        // Root must be 1 and cannot have a parent
        ensuref(v != 1,
                "Node 1 is the root but appears as a child in edge %d: (%d -> %d)", i+1, u, v);
        // No multiple parents
        ensuref(parent[v] == 0,
                "Multiple parents detected for node %d at edge %d: previous parent %d, new parent %d",
                v, i+1, parent[v], u);
        parent[v] = u;
    }

    // Check root has no parent
    ensuref(parent[1] == 0,
            "Root node 1 should have no parent, but parent[1] = %d", parent[1]);
    // Check every other node has exactly one parent
    for (int v = 2; v <= N; v++) {
        ensuref(parent[v] != 0,
                "Node %d has no parent", v);
    }

    // Finally, ensure EOF immediately after the last newline
    inf.readEof();
    return 0;
}
