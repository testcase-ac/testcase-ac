#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    inf.readInts(n, 0, 7, "A_i");
    inf.readEoln();

    bool hasTypeTwo = false;
    for (int i = 1; i <= m; ++i) {
        int q = inf.readInt(1, 2, "q_i");
        inf.readSpace();

        if (q == 1) {
            inf.readInt(1, n, "a_i");
            inf.readSpace();
            inf.readInt(0, 7, "b_i");
        } else {
            hasTypeTwo = true;
            int a = inf.readInt(1, n - 1, "a_i");
            inf.readSpace();
            inf.readInt(a + 1, n, "b_i");
        }
        inf.readEoln();
    }

    ensuref(hasTypeTwo, "at least one query must have q_i = 2");
    inf.readEof();
}
