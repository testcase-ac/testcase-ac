#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 4000, "N");
    inf.readSpace();
    int K = inf.readInt(1, min(N, 800), "K");
    inf.readEoln();

    vector< vector<int> > u(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        u[i][0] = inf.readInt(0, 9, "u_ij");
        for (int j = 1; j < N; ++j) {
            inf.readSpace();
            u[i][j] = inf.readInt(0, 9, "u_ij");
        }
        inf.readEoln();
    }

    // Validate matrix properties: u_ii = 0, symmetry u_ij = u_ji
    for (int i = 0; i < N; ++i) {
        ensuref(u[i][i] == 0, "Diagonal element u_%d%d must be 0, but is %d", i + 1, i + 1, u[i][i]);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            ensuref(u[i][j] == u[j][i],
                    "Matrix must be symmetric: u_%d%d=%d, u_%d%d=%d",
                    i + 1, j + 1, u[i][j],
                    j + 1, i + 1, u[j][i]);
        }
    }

    inf.readEof();
}
