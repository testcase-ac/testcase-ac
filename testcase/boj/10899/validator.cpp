#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 1000000000, "P");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, p - 1, "time_i");
    }
    inf.readEoln();
    inf.readEof();
}
