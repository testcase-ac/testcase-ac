#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 1000000, "a");
    inf.readSpace();
    int b = inf.readInt(a, 1000000, "b");
    inf.readSpace();
    int c = inf.readInt(1, 1000000, "c");
    inf.readSpace();
    inf.readInt(c, 1000000, "d");
    inf.readEoln();
    inf.readEof();
}
