#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(3, 40, "K");
    inf.readSpace();
    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, k, "x");
        inf.readSpace();
        inf.readInt(x, k, "y");
        inf.readSpace();
        inf.readInt(0, 1000, "r");
        inf.readEoln();
    }

    inf.readEof();
}
