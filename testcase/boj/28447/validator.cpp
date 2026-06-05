#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            c[i][j] = inf.readInt(-1000, 1000, "C_i_j");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref(c[i][i] == 0, "C[%d][%d] must be 0, found %d", i + 1, i + 1, c[i][i]);
        for (int j = i + 1; j < n; ++j) {
            ensuref(c[i][j] == c[j][i],
                    "C[%d][%d] = %d differs from C[%d][%d] = %d",
                    i + 1,
                    j + 1,
                    c[i][j],
                    j + 1,
                    i + 1,
                    c[j][i]);
        }
    }

    inf.readEof();
}
