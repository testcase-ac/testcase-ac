#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 100000, "m_ij");
        }
        inf.readEoln();
    }

    int r = inf.readInt(1, n, "r");
    inf.readSpace();
    int c = inf.readInt(1, n, "c");
    inf.readEoln();

    ensuref(!(r == 1 && c == 1), "Y must not be the start cell");
    ensuref(!(r == n && c == n), "Y must not be the destination cell");

    inf.readEof();
}
