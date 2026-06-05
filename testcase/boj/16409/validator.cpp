#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10000000, "b");
    inf.readSpace();
    int c = inf.readInt(1, 10000000, "c");
    inf.readSpace();
    int d = inf.readInt(1, 10000000, "d");
    inf.readEoln();

    ensuref(a <= b, "expected a <= b, got a=%d b=%d", a, b);
    ensuref(c <= d, "expected c <= d, got c=%d d=%d", c, d);

    inf.readEof();
}
