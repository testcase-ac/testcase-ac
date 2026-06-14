#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 100, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
