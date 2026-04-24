#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    // Maximum number of edges is n*(n-1)/2
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    // Prepare adjacency to detect loops and multiple edges
    vector<vector<char>> seen(n+1, vector<char>(n+1, 0));

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        // No loops allowed
        ensuref(u != v,
                "Loop detected at edge %d: (%d, %d)",
                i+1, u, v);

        // Normalize order for undirected check
        int a = min(u, v);
        int b = max(u, v);

        // No multiple edges allowed
        ensuref(!seen[a][b],
                "Multiple edges detected at edge %d: (%d, %d)",
                i+1, u, v);

        seen[a][b] = seen[b][a] = 1;
    }

    // No extra content
    inf.readEof();
    return 0;
}
