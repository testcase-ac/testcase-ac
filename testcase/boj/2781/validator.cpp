#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap aggregate cells to one
    // largest testcase by the local validator policy for omitted multi-case limits.
    const int maxT = 100000;
    const int maxTotalCells = 2500;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    int totalCells = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "N");
        inf.readSpace();
        int m = inf.readInt(1, 50, "M");
        inf.readEoln();

        totalCells += n * m;
        ensuref(totalCells <= maxTotalCells,
                "sum of N*M exceeds %d at case %d", maxTotalCells, tc);

        for (int i = 1; i <= n; ++i) {
            string row = inf.readToken("[1-9]{1,50}", "C_i");
            ensuref((int)row.size() == m,
                    "row %d has length %d, expected %d", i, (int)row.size(), m);
            inf.readEoln();
        }

        inf.readInt(1, n, "Sx");
        inf.readSpace();
        inf.readInt(1, m, "Sy");
        inf.readSpace();
        inf.readInt(1, n, "Dx");
        inf.readSpace();
        inf.readInt(1, m, "Dy");
        inf.readEoln();
    }

    inf.readEof();
}
