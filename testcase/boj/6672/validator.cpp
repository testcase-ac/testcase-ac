#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        // Read number of power plants (P) and number of connections (C)
        int P = inf.readInt(0, 10000, "P");
        inf.readSpace();
        // Maximum possible edges in an undirected simple graph is P*(P-1)/2
        long long maxEdges = (long long)P * (P - 1) / 2;
        int C = inf.readInt(0, maxEdges, "C");
        inf.readEoln();

        // Check for the terminating "0 0" line
        if (P == 0 && C == 0) {
            break;
        }

        // Build an adjacency bit‐matrix to detect loops and multiple edges
        // Use vector<bool> for packing bits: total ≈ P*P bits, which is ≤10000*10000 ≈ 100M bits (~12.5MB)
        vector< vector<bool> > seen(P, vector<bool>(P, false));

        for (int i = 0; i < C; i++) {
            int p1 = inf.readInt(0, P - 1, "p1");
            inf.readSpace();
            int p2 = inf.readInt(0, P - 1, "p2");
            inf.readEoln();

            // No loops allowed (p1 != p2)
            ensuref(p1 != p2,
                    "Loop detected at connection %d: (%d, %d)",
                    i, p1, p2);

            // No multiple edges: check both directions in the matrix
            ensuref(!seen[p1][p2],
                    "Multiple connections detected at connection %d: (%d, %d)",
                    i, p1, p2);

            // Mark the edge both ways
            seen[p1][p2] = seen[p2][p1] = true;
        }
    }

    inf.readEof();
    return 0;
}
