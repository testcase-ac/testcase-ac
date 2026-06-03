#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int b1 = inf.readInt(1, 30, "b1");
    inf.readSpace();
    int b2 = inf.readInt(1, 30, "b2");
    inf.readSpace();
    int b3 = inf.readInt(1, 30, "b3");
    inf.readEoln();

    ensuref(b1 < b2 && b2 < b3, "move sizes must satisfy b1 < b2 < b3");

    for (int i = 1; i <= 5; ++i) {
        int k1 = inf.readInt(1, 500, "k1");
        inf.readSpace();
        int k2 = inf.readInt(1, 500, "k2");
        inf.readEoln();
    }

    inf.readEof();
}
