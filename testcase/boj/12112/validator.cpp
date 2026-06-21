#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000000, "A");
    inf.readSpace();
    int b = inf.readInt(1, 10000000, "B");
    inf.readEoln();

    ensuref(a <= b, "A must be at most B, got A=%d and B=%d", a, b);

    inf.readEof();
}
