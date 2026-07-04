#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 50000, "s");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 1000000000, "d");
        inf.readSpace();
        inf.readToken("y|n", "t");
        inf.readEoln();
    }

    inf.readEof();
}
