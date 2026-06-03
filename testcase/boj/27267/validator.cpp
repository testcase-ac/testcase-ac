#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "a");
    inf.readSpace();
    inf.readInt(1, 1000, "b");
    inf.readSpace();
    inf.readInt(1, 1000, "c");
    inf.readSpace();
    inf.readInt(1, 1000, "d");
    inf.readEoln();
    inf.readEof();
}
