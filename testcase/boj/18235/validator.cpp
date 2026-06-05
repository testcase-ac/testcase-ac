#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();

    ensuref(a != b, "A and B must be distinct: A=%d, B=%d", a, b);

    inf.readEof();
}
