#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(-100, 100, "A");
    inf.readSpace();
    int b = inf.readInt(-100, 100, "B");
    inf.readSpace();
    int c = inf.readInt(-100, 100, "C");
    inf.readEoln();

    ensuref(a != 0, "A must be nonzero");
    ensuref(b != 0, "B must be nonzero");
    ensuref(c != 0, "C must be nonzero");

    inf.readEof();
}
