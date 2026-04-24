#include "testlib.h"
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 16, "N");
    inf.readEoln();

    // Read cost matrix W
    vector<vector<int>> W(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        // Each row has exactly N integers in [0,1e6]
        vector<int> row = inf.readInts(N, 0, 1000000, 
                                       ("W_row_" + to_string(i+1)).c_str());
        inf.readEoln();
        for (int j = 0; j < N; j++) {
            W[i][j] = row[j];
        }
        // Diagonal must be zero
        ensuref(W[i][i] == 0, "W[%d][%d] must be 0 (diagonal)", i+1, i+1);
    }

    // Validate that there is at least one Hamiltonian cycle
    // DP over subsets: dp[mask][u] = reachable mask ending at u
    int fullMask = 1 << N;
    vector< vector<char> > dp(fullMask, vector<char>(N, 0));
    for (int i = 0; i < N; i++) {
        dp[1<<i][i] = 1;
    }
    for (int mask = 1; mask < fullMask; mask++) {
        for (int u = 0; u < N; u++) {
            if (!dp[mask][u]) continue;
            // Try to go to v not in mask
            for (int v = 0; v < N; v++) {
                if (mask & (1<<v)) continue;
                if (W[u][v] != 0) {
                    dp[mask | (1<<v)][v] = 1;
                }
            }
        }
    }
    bool hasCycle = false;
    int all = fullMask - 1;
    for (int u = 0; u < N && !hasCycle; u++) {
        if (!dp[all][u]) continue;
        // check edge back to some start s
        for (int s = 0; s < N; s++) {
            if (W[u][s] != 0) {
                hasCycle = true;
                break;
            }
        }
    }
    ensuref(hasCycle, "Input must admit at least one Hamiltonian cycle");

    inf.readEof();
    return 0;
}
