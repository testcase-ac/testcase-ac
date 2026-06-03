#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    int m = inf.readInt(0, 100, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n - 1, "x");
        inf.readSpace();
        int y = inf.readInt(x + 1, n, "y");
        inf.readEoln();
    }

    inf.readEof();
}
