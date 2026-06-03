#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    int a = inf.readInt(0, 1000, "a");
    inf.readSpace();
    int b = inf.readInt(0, 1000, "b");
    inf.readEoln();

    ensuref(a < b, "expected a < b, got a=%d b=%d", a, b);

    inf.readEof();
}
