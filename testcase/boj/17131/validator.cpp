#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int minCoord = -200000;
    const int maxCoord = 200000;

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(minCoord, maxCoord, "x");
        inf.readSpace();
        inf.readInt(minCoord, maxCoord, "y");
        inf.readEoln();
    }

    // CHECK: the statement gives star coordinates but does not require them to be distinct.
    inf.readEof();
}
