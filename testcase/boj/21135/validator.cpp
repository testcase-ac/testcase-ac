#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int c = inf.readInt(1, 100000, "c");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, c, "w");
        inf.readEoln();
    }

    inf.readEof();
}
