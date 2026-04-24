#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 400, "n");
    inf.readSpace();
    int k = inf.readInt(1, 50000, "k");
    inf.readEoln();

    // Read the k known precedence relations
    // We'll build an adjacency matrix for cycle detection
    static bool reach[405][405];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            reach[i][j] = false;
        }
    }

    for (int i = 0; i < k; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();
        // No self-loop allowed, implies contradiction
        ensuref(u != v,
                "Relation %d is a loop: event %d before itself", 
                i+1, u);
        // Record the direct edge
        reach[u][v] = true;
    }

    // Read s, the number of queries
    int s = inf.readInt(1, 50000, "s");
    inf.readEoln();

    // Read the s query pairs
    for (int i = 0; i < s; i++) {
        int a = inf.readInt(1, n, "a_j");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_j");
        inf.readEoln();
        // Query events must be distinct
        ensuref(a != b,
                "Query %d has identical events: %d and %d",
                i+1, a, b);
    }

    // Check for cycles via Floyd–Warshall on the reachability matrix
    for (int mid = 1; mid <= n; mid++) {
        for (int i = 1; i <= n; i++) {
            if (!reach[i][mid]) continue;
            for (int j = 1; j <= n; j++) {
                if (reach[mid][j]) {
                    reach[i][j] = true;
                }
            }
        }
    }
    // Ensure no node reaches itself
    for (int i = 1; i <= n; i++) {
        ensuref(!reach[i][i],
                "Cycle detected involving event %d", i);
    }

    inf.readEof();
    return 0;
}
