#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int w = inf.readInt(1, n, "W");
    inf.readEoln();

    for (int i = 1; i <= w; ++i) {
        inf.readInt(1, n, "x_i");
        inf.readSpace();
        inf.readInt(1, n, "y_i");
        inf.readEoln();
    }

    for (int i = 1; i <= n; ++i) {
        string row = inf.readToken("[01]{1,1000}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i,
                (int)row.size(), n);
        if (i == 1) {
            ensuref(row[0] == '1', "start cell (1, 1) must contain a stone");
        }
        if (i == n) {
            ensuref(row[n - 1] == '1',
                    "destination cell (%d, %d) must contain a stone", n, n);
        }
        inf.readEoln();
    }

    // CHECK: The statement gives W source positions but does not require them to be distinct.
    inf.readEof();
}
