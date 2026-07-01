#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(0, 100000, "A");
    inf.readSpace();
    int b = inf.readInt(0, 100000, "B");
    inf.readEoln();

    ensuref(a + b >= 1, "A + B must be at least 1, found %d", a + b);
    ensuref(a + b <= 100000, "A + B must be at most 100000, found %d", a + b);

    inf.readEof();
}
