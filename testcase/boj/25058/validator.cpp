#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int case_index = 1; case_index <= t; ++case_index) {
        setTestCase(case_index);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            int r = inf.readInt(0, 100, "r_i");
            inf.readSpace();
            int w = inf.readInt(0, 100, "w_i");
            inf.readEoln();

            ensuref(r + w >= 1, "critic %d requests no bottles", i);
        }
    }

    inf.readEof();
}
