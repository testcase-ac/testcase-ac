#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int b = inf.readInt(a, 100000, "B");
    inf.readEoln();
    inf.readEof();
}
