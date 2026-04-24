#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities
    int N = inf.readInt(2, 1500, "N");
    inf.readEoln();

    // Read distance matrix
    vector<vector<int>> mat(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Prepare a name for clear error messages
            string name = "w[" + to_string(i+1) + "][" + to_string(j+1) + "]";
            int w = inf.readInt(0, 1000, name);
            if (j + 1 < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            // Diagonal must be zero, off-diagonals strictly positive
            if (i == j) {
                ensuref(w == 0,
                        "Diagonal element %s must be 0 but is %d",
                        name.c_str(), w);
            } else {
                ensuref(w > 0,
                        "Off-diagonal element %s must be positive but is %d",
                        name.c_str(), w);
            }

            // Symmetry check with the previously read entry
            if (j < i) {
                int sym = mat[j][i];
                ensuref(w == sym,
                        "Matrix not symmetric at %s and w[%d][%d]: %d vs %d",
                        name.c_str(), j+1, i+1, sym, w);
            }

            mat[i][j] = w;
        }
    }

    // No extra characters after the matrix
    inf.readEof();
    return 0;
}
