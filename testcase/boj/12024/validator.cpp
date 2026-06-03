#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250, "n");
    inf.readEoln();

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            a[i][j] = inf.readInt(0, 1, "a_ij");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        ensuref(a[i][i] == 0, "diagonal entry a[%d][%d] must be 0", i + 1, i + 1);
        for (int j = i + 1; j < n; ++j) {
            ensuref(a[i][j] == a[j][i],
                    "matrix must be symmetric at (%d, %d) and (%d, %d)",
                    i + 1, j + 1, j + 1, i + 1);
        }
    }

    inf.readEof();
}
