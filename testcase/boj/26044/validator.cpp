#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000000, "N");
        inf.readEoln();
    }

    inf.readEof();
}
