#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 50, "R");
    inf.readSpace();
    int c = inf.readInt(1, 50, "C");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "D");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "W");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readLong(1LL, 1000000000LL, "y");
        }
        inf.readEoln();
    }

    inf.readEof();
}
