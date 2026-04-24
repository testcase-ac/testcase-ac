#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Keep track of existing undirected edges
    set<pair<int,int>> edges;

    for (int i = 1; i <= M; i++) {
        // Read query type and endpoints
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();

        // No loops allowed
        ensuref(A != B,
                "Query %d: loop detected (A == B == %d)",
                i, A);

        // Canonical undirected edge representation
        int u = min(A, B);
        int v = max(A, B);
        pair<int,int> e = make_pair(u, v);

        if (type == 1) {
            // Add edge: must not already exist
            ensuref(!edges.count(e),
                    "Query %d: adding existing edge (%d, %d)",
                    i, u, v);
            edges.insert(e);
        }
        else if (type == 2) {
            // Remove edge: must exist
            ensuref(edges.count(e),
                    "Query %d: removing non-existent edge (%d, %d)",
                    i, u, v);
            edges.erase(e);
        }
        else {
            // type == 3: just a connectivity query; no state change
        }
    }

    inf.readEof();
    return 0;
}
