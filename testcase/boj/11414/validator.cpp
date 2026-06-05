#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000000, "A");
    inf.readSpace();
    inf.readInt(1, 1000000000, "B");
    inf.readEoln();
    inf.readEof();
}
