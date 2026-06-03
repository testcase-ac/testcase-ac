#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d1 = inf.readInt(1, 99, "d1");
    inf.readSpace();
    int d2 = inf.readInt(1, 99, "d2");
    inf.readSpace();
    inf.readInt(1, 99, "chi");
    inf.readEoln();

    ensuref(d1 != d2, "d1 and d2 must be different: %d", d1);

    inf.readEof();
}
