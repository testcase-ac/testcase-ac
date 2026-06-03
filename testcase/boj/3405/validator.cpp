#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 20;
    const int maxAbsDebt = 1000000;
    const long long maxMatrixEntries = 5000000;

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long matrixEntries = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, maxN, "n");
        inf.readEoln();

        matrixEntries += 1LL * n * n;
        // CHECK: The statement does not bound T; cap total scalar matrix entries.
        ensuref(matrixEntries <= maxMatrixEntries,
                "total matrix entries exceeds %lld at case %d", maxMatrixEntries, tc);

        vector<vector<int>> d(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                d[i][j] = inf.readInt(-maxAbsDebt, maxAbsDebt, "d_ij");
            }
            inf.readEoln();
        }

        for (int i = 0; i < n; ++i) {
            ensuref(d[i][i] == 0, "case %d has d_%d_%d = %d, expected 0",
                    tc, i + 1, i + 1, d[i][i]);
            for (int j = i + 1; j < n; ++j) {
                ensuref(d[i][j] == -d[j][i],
                        "case %d has d_%d_%d = %d and d_%d_%d = %d",
                        tc, i + 1, j + 1, d[i][j], j + 1, i + 1, d[j][i]);
            }
        }
    }

    inf.readEof();
    return 0;
}
