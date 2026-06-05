#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000000LL, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(0LL, 1000000000000LL, "A_i");
    }
    inf.readEoln();

    inf.readEof();
}
