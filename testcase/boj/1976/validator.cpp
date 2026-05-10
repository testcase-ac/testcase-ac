#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities N (1 ≤ N ≤ 200)
    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    // Read length of travel plan M (1 ≤ M ≤ 1000)
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read adjacency matrix: N lines, each with N entries 0 or 1
    vector<vector<int>> adj(N+1, vector<int>(N+1));
    for (int i = 1; i <= N; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "adj");
        inf.readEoln();
        for (int j = 1; j <= N; j++) {
            adj[i][j] = row[j-1];
        }
    }

    // Validate no self‐loops and symmetry of the adjacency matrix
    for (int i = 1; i <= N; i++) {
        ensuref(adj[i][i] == 0,
                "Self‐loop detected at (%d,%d): entry must be 0", i, i);
        for (int j = i + 1; j <= N; j++) {
            ensuref(adj[i][j] == adj[j][i],
                    "Asymmetry detected at (%d,%d): %d vs %d",
                    i, j, adj[i][j], adj[j][i]);
        }
    }

    // Read the travel plan: M city indices in [1, N]
    vector<int> plan = inf.readInts(M, 1, N, "plan");
    inf.readEoln();

    // File must end immediately after the last newline
    inf.readEof();
    return 0;
}
