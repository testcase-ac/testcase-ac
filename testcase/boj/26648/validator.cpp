#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int row = 0; row < 3; ++row) {
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readLong(0LL, 2000000000LL, row == 0 ? "A_i" : row == 1 ? "B_i" : "C_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
