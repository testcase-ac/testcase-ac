#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(2, 200, "w");
    inf.readSpace();
    int h = inf.readInt(2, 200, "h");
    inf.readEoln();

    int x = inf.readInt(1, w, "x");
    inf.readSpace();
    inf.readInt(1, h, "y");
    inf.readEoln();

    inf.readEof();
}
