#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int x = inf.readInt(1000 * n, 5000 * n, "X");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "A");
        inf.readSpace();
        inf.readInt(1, 10000, "B");
        inf.readEoln();
    }

    inf.readEof();
}
