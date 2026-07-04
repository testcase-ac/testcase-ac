#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        double a = inf.readStrictDouble(0.0, 100000.0, 1, 1, "a_i");
        inf.readSpace();
        double b = inf.readStrictDouble(a, 100000.0, 1, 1, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
