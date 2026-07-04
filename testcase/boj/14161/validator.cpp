#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000, "A");
    inf.readSpace();
    inf.readInt(1, 100000, "B");
    inf.readEoln();
    inf.readEof();
}
