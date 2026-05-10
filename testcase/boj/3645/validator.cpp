#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <cassert>
using namespace std;

// Helper: check if x is a power of two
bool is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 2;
    const int MAX_N = 1024;

    int test_case = 0;
    while (!inf.seekEof()) {
        ++test_case;

        // Read n
        int n = inf.readInt(MIN_N, MAX_N, "n");
        ensuref(is_power_of_two(n), "n=%d is not a power of two in test case %d", n, test_case);
        inf.readEoln();

        // Read n lines of n-length binary strings
        vector<string> mat(n);
        for (int i = 0; i < n; ++i) {
            mat[i] = inf.readLine("[01]{"+to_string(n)+"}", "adjacency_row");
            ensuref((int)mat[i].size() == n, "Row %d does not have length n=%d in test case %d", i+1, n, test_case);

            // Diagonal must be 0
            ensuref(mat[i][i] == '0', "Diagonal element mat[%d][%d] must be 0 in test case %d", i+1, i+1, test_case);
        }

        // For all i != j: mat[i][j] != mat[j][i], and both are in {0,1}
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ensuref(mat[i][j] == '0' || mat[i][j] == '1', "mat[%d][%d] is not 0 or 1 in test case %d", i+1, j+1, test_case);
                if (i != j) {
                    ensuref(mat[i][j] != mat[j][i], "mat[%d][%d] == mat[%d][%d] == %c for i != j in test case %d", i+1, j+1, j+1, i+1, mat[i][j], test_case);
                }
            }
        }

        // Global property 1: Team 1 can beat at least half of the teams (excluding itself)
        int team1_wins = 0;
        for (int j = 0; j < n; ++j) {
            if (j == 0) continue; // skip self
            if (mat[0][j] == '1') ++team1_wins;
        }
        ensuref(team1_wins >= n/2, "Team 1 must be able to beat at least half of the teams (got %d, need at least %d) in test case %d", team1_wins, n/2, test_case);

        // Global property 2: For every team t that team 1 cannot beat, there exists t' such that
        // team 1 beats t', and t' beats t.
        for (int t = 1; t < n; ++t) {
            if (mat[0][t] == '1') continue; // team 1 can beat t
            bool found = false;
            for (int t2 = 1; t2 < n; ++t2) {
                if (mat[0][t2] == '1' && mat[t2][t] == '1') {
                    found = true;
                    break;
                }
            }
            ensuref(found, "For team t=%d (team 1 cannot beat), there is no t' such that team 1 beats t' and t' beats t in test case %d", t+1, test_case);
        }
    }

    inf.readEof();
}
