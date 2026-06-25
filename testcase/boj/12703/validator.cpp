#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(2, 20, "N");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        int m = inf.readInt(3, 29, "M");
        inf.readSpace();
        inf.readInt(0, 1, "V");
        inf.readEoln();

        ensuref(m % 2 == 1, "M must be odd, found %d", m);

        int interior_count = (m - 1) / 2;
        int leaf_count = (m + 1) / 2;

        for (int i = 1; i <= interior_count; ++i) {
            inf.readInt(0, 1, "G");
            inf.readSpace();
            inf.readInt(0, 1, "C");
            inf.readEoln();
        }

        for (int i = 1; i <= leaf_count; ++i) {
            inf.readInt(0, 1, "I");
            inf.readEoln();
        }
    }

    inf.readEof();
}
