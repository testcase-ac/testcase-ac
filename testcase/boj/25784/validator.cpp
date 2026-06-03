#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(2, 1000, "a");
    inf.readSpace();
    int b = inf.readInt(2, 1000, "b");
    inf.readSpace();
    int c = inf.readInt(2, 1000, "c");
    inf.readEoln();

    ensuref(a != b && a != c && b != c,
            "the three integers must be distinct: %d %d %d", a, b, c);

    inf.readEof();
}
