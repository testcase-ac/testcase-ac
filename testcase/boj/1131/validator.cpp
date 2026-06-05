#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int b = inf.readInt(a, 1000000, "B");
    inf.readSpace();
    inf.readInt(1, 6, "K");
    inf.readEoln();
    inf.readEof();
}
