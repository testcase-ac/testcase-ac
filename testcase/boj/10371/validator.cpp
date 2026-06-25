#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int m = inf.readInt(1, 100, "M");
        inf.readSpace();
        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        for (int row = 1; row <= m; ++row) {
            string layout = inf.readToken("[01]{1,100}", "row");
            ensuref(static_cast<int>(layout.size()) == n,
                    "row %d has length %d, expected %d",
                    row,
                    static_cast<int>(layout.size()),
                    n);
            inf.readEoln();
        }
    }

    inf.readEof();
}
