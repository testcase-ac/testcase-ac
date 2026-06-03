#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(-100, 100, "A");
    inf.readEoln();
    ensuref(a != 0, "A must not be 0");

    int b = inf.readInt(1, 100, "B");
    inf.readEoln();
    ensuref(a < b, "A must be less than B");

    inf.readInt(1, 100, "C");
    inf.readEoln();
    inf.readInt(1, 100, "D");
    inf.readEoln();
    inf.readInt(1, 100, "E");
    inf.readEoln();

    inf.readEof();
}
