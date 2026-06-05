#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(2, 1000, "A");
    inf.readSpace();
    int b = inf.readInt(a, 1000, "B");
    inf.readEoln();

    int c = inf.readInt(2, 1000, "C");
    inf.readSpace();
    inf.readInt(c, 1000, "D");
    inf.readEoln();

    inf.readEof();
}
