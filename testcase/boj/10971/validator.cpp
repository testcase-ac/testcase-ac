#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 10, "N");
    inf.readEoln();

    // Read cost matrix W
    vector<vector<int>> W(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 1000000, "W");
        for (int j = 0; j < N; j++) {
            W[i][j] = row[j];
        }
        inf.readEoln();
    }

    // Validate diagonal entries are zero
    for (int i = 0; i < N; i++) {
        ensuref(W[i][i] == 0, "W[%d][%d] must be 0, found %d", i+1, i+1, W[i][i]);
    }

    // Build adjacency: directed edge i->j exists iff i!=j and W[i][j] > 0
    vector<vector<bool>> adj(N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j && W[i][j] > 0) {
                adj[i][j] = true;
            }
        }
    }

    // Check existence of a Hamiltonian cycle in this directed graph
    bool has_cycle = false;
    int FULL = (1 << N) - 1;
    // Try each starting city s
    for (int s = 0; s < N && !has_cycle; s++) {
        // dp[mask][v] = can start at s, visit exactly mask, end at v
        vector<vector<char>> dp(1<<N, vector<char>(N, 0));
        dp[1<<s][s] = 1;
        for (int mask = 0; mask <= FULL; mask++) {
            if (!(mask & (1<<s))) continue;
            for (int v = 0; v < N; v++) {
                if (!dp[mask][v]) continue;
                // try to go to u not in mask
                for (int u = 0; u < N; u++) {
                    if (!(mask & (1<<u)) && adj[v][u]) {
                        dp[mask | (1<<u)][u] = 1;
                    }
                }
            }
        }
        // Check if we can return to s
        for (int v = 0; v < N; v++) {
            if (dp[FULL][v] && adj[v][s]) {
                has_cycle = true;
                break;
            }
        }
    }
    ensuref(has_cycle, "No Hamiltonian cycle exists in the given cost matrix");

    inf.readEof();
    return 0;
}
