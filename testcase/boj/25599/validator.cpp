#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "R");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 10000000, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
