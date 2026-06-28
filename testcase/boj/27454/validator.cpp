#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n + 1, "K");
    inf.readEoln();

    inf.readLong(1LL, 1000000000LL, "Y");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "v_i");
    }
    inf.readEoln();

    inf.readEof();
}
