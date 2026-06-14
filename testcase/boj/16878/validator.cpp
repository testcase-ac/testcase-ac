#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        inf.readInt(1, 10000000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
