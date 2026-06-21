#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(0, 5, "H");
    inf.readSpace();
    int w = inf.readInt(1, 200, "W");
    inf.readEoln();

    inf.readEof();
}
