#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400000, "N");
    inf.readSpace();
    int k = inf.readInt(100, 1000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 60, "A_i");
        inf.readSpace();
        inf.readInt(0, 60, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
