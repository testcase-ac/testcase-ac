#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    ensuref(n % 2 == 0, "n must be even: %d", n);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-10000, 10000, "a_i_1");
        inf.readSpace();
        inf.readInt(-10000, 10000, "a_i_2");
        inf.readSpace();
        inf.readInt(-10000, 10000, "a_i_3");
        inf.readEoln();
    }

    inf.readEof();
}
