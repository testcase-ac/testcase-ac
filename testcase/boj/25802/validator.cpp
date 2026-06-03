#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(0, 9, "a");
    inf.readSpace();
    int b = inf.readInt(0, 9, "b");
    inf.readEoln();

    ensuref(a != 0 || b != 0, "at least one starting number must be nonzero");

    inf.readEof();
}
