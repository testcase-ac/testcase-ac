#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1000000000, "c");
        inf.readEoln();
    }

    inf.readEof();
}
