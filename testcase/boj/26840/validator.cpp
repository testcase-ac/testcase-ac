#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int b = inf.readInt(2, 1000000, "B");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < b; ++i) {
        inf.readInt(1, 1000000, "a_i");
        if (i + 1 == b) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    for (int i = 0; i < q; ++i) {
        inf.readLong(0LL, 1000000000000000000LL, "k_i");
        inf.readEoln();
    }

    inf.readEof();
}
