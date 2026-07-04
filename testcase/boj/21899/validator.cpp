#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMax = 200000;

    int n = inf.readInt(1, kMax, "n");
    inf.readSpace();
    inf.readInt(1, kMax, "t");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, kMax, "a_i");
        inf.readSpace();
        inf.readInt(1, kMax, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
