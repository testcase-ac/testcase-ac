#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 2000, "S");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000, "V_i");
        inf.readSpace();
        inf.readInt(1, s, "W_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "K_i");
        inf.readEoln();
    }

    inf.readEof();
}
