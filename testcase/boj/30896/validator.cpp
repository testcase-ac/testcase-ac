#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100, "A_i");
        inf.readSpace();
        inf.readInt(1, 100, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
