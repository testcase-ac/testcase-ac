#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 100, "A");
    inf.readSpace();
    int b = inf.readInt(1, 100, "B");
    inf.readSpace();
    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    ensuref(a != b, "A and B must be distinct: %d", a);
    ensuref(a != c, "A and C must be distinct: %d", a);
    ensuref(b != c, "B and C must be distinct: %d", b);

    inf.readEof();
}
