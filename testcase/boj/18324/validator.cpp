#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000000, "K");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 100000, "X");
        inf.readEoln();
    }

    inf.readEof();
}
