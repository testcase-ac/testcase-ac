#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 9, "N");
    inf.readSpace();
    int m = inf.readInt(1, 9, "M");
    inf.readEoln();

    ensuref(2 <= n * m && n * m <= 9, "N*M must be between 2 and 9, got %d", n * m);

    inf.readEof();
}
