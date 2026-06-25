#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(0, 1000, "A");
    inf.readSpace();
    int b = inf.readInt(0, 1000, "B");
    inf.readSpace();
    inf.readInt(-2000, 2000, "K");
    inf.readEoln();

    ensuref(a + b > 0, "A+B must be positive: A=%d, B=%d", a, b);

    inf.readEof();
}
