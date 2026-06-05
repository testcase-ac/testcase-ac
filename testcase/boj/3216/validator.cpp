#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000, "d");
        inf.readSpace();
        inf.readInt(1, 1000, "v");
        inf.readEoln();
    }

    inf.readEof();
}
