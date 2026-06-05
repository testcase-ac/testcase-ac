#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int x = inf.readInt(0, 100000000, "x");
    inf.readEoln();

    for (int expectedDegree = n; expectedDegree >= 0; --expectedDegree) {
        int coefficient = inf.readInt(0, 100, "A_i");
        inf.readSpace();
        int degree = inf.readInt(expectedDegree, expectedDegree, "i");
        inf.readEoln();
        (void)coefficient;
        (void)degree;
    }

    inf.readEof();
}
