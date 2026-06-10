#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 100, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 50, "A_i");
        inf.readSpace();
        inf.readInt(1, 50, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
