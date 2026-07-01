#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(2, 200000, "P");
    ensuref(p % 2 == 0, "P must be even: %d", p);
    inf.readEoln();
    inf.readEof();
}
