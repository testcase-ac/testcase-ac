#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1000, 9999, "a");
    inf.readSpace();
    int b = inf.readInt(1000, 9999, "b");
    inf.readSpace();
    inf.readInt(0, 9, "d");
    inf.readEoln();

    ensuref(a <= b, "range start must not exceed range end: %d > %d", a, b);

    inf.readEof();
}
