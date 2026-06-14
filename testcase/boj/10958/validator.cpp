#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 40, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 10000000000000000LL, "cost_i");
    }
    inf.readEoln();
    inf.readEof();
}
