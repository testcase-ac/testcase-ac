#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n1 = inf.readInt(1, 10000, "n1");
    inf.readSpace();
    int n2 = inf.readInt(1, 10000, "n2");
    inf.readEoln();

    ensuref(n1 < n2, "n1 must be less than n2: n1=%d, n2=%d", n1, n2);

    inf.readEof();
}
