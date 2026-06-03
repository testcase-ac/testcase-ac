#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "n");
    inf.readEoln();

    for (int case_index = 1; case_index <= 3; ++case_index) {
        setTestCase(case_index);
        inf.readInts(n, -10000, 10000, "a");
        inf.readEoln();
    }

    inf.readEof();
}
