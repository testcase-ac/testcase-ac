#include "testlib.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int x = inf.readInt(1, 2 * n - 1, "x");
    inf.readSpace();
    int maxY = 2 * n - 1 - std::abs(x - n);
    inf.readInt(1, maxY, "y");
    inf.readEoln();
    inf.readEof();
}
