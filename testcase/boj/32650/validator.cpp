#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    long long maxM = min((long long)n * (n - 1) / 2, 100000LL);
    int m = inf.readInt(0, maxM, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    // Read array a
    inf.readInts(n, 1, 100000, "a_i");
    inf.readEoln();

    // Validate edges: no loops, no multiple edges
    vector<vector<char>> seen(n + 1, vector<char>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int z = inf.readInt(1, 100000, "z_i");
        inf.readEoln();

        ensuref(x != y,
                "Loop detected at edge index %d: (%d, %d)", i, x, y);
        int u = min(x, y), v = max(x, y);
        ensuref(!seen[u][v],
                "Multiple edges detected at edge index %d: (%d, %d)", i, x, y);
        seen[u][v] = seen[v][u] = 1;
    }

    inf.readEof();
    return 0;
}
