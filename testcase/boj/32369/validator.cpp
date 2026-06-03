#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int a = inf.readInt(1, 10, "A");
    inf.readSpace();
    int b = inf.readInt(1, 10, "B");
    inf.readEoln();

    ensuref(a < b, "A must be less than B: A = %d, B = %d", a, b);
    inf.readEof();
}
