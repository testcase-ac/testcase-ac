#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 300, "N");
    inf.readEoln();

    // Read well costs W_i
    vector<int> W(N);
    for (int i = 0; i < N; i++) {
        string name = "W_" + to_string(i+1);
        W[i] = inf.readInt(1, 100000, name.c_str());
        inf.readEoln();
    }

    // Read pipe cost matrix P_{i,j}
    vector<vector<int>> P(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            string name = "P_" + to_string(i+1) + "_" + to_string(j+1);
            int val;
            if (i == j) {
                // diagonal must be 0
                val = inf.readInt(0, 0, name.c_str());
            } else {
                // off-diagonal must be between 1 and 100000
                val = inf.readInt(1, 100000, name.c_str());
            }
            P[i][j] = val;

            if (j + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Validate symmetry P[i][j] == P[j][i]
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            ensuref(P[i][j] == P[j][i],
                    "P[%d][%d] != P[%d][%d]: %d vs %d",
                    i+1, j+1, j+1, i+1, P[i][j], P[j][i]);
        }
    }

    inf.readEof();
    return 0;
}
