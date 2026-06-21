#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    vector<vector<int>> d(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            d[i][j] = inf.readInt(0, 200, "d_i_j");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref(d[i][i] == 0, "distance from town %d to itself is %d", i + 1, d[i][i]);
        for (int j = i + 1; j < n; ++j) {
            ensuref(d[i][j] == d[j][i],
                    "distance matrix is not symmetric at (%d, %d): %d != %d",
                    i + 1,
                    j + 1,
                    d[i][j],
                    d[j][i]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                ensuref(d[i][j] <= d[i][k] + d[k][j],
                        "triangle inequality fails for towns %d, %d, %d: %d > %d + %d",
                        i + 1,
                        j + 1,
                        k + 1,
                        d[i][j],
                        d[i][k],
                        d[k][j]);
            }
        }
    }

    inf.readEof();
}
