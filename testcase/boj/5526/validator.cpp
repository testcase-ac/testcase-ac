#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000000, "P_i");
        inf.readEoln();
    }

    inf.readEof();
}
