#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(-1000000000, 1000000000, "a");
    ensuref(a != 0, "a must be nonzero");
    inf.readEoln();
    inf.readEof();
}
