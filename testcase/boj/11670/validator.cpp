#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2500, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000000, 1000000, "a");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
