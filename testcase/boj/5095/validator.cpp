#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100;
    const int MAX_M = 32000;
    const int MAX_P = 32000;
    // CHECK: the statement does not bound the number of problems; cap scalar
    // matrix values below the local practical limit for primarily numeric input.
    const int MAX_MATRIX_VALUES = 4900000;

    int totalMatrixValues = 0;
    int caseIndex = 0;
    while (true) {
        int n = inf.readInt(0, MAX_N, "N");
        inf.readSpace();
        int m = inf.readInt(0, MAX_M, "M");
        inf.readSpace();
        int p = inf.readInt(0, MAX_P, "P");
        inf.readEoln();

        if (n == 0 || m == 0 || p == 0) {
            ensuref(n == 0 && m == 0 && p == 0,
                    "only the terminator line may contain zeroes, got %d %d %d",
                    n, m, p);
            break;
        }

        ++caseIndex;
        setTestCase(caseIndex);

        ensuref(totalMatrixValues <= MAX_MATRIX_VALUES - n * n,
                "too many matrix values before case %d", caseIndex);
        totalMatrixValues += n * n;

        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (col > 0) {
                    inf.readSpace();
                }
                inf.readInt(0, m - 1, "i");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
