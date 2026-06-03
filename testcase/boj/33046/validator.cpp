#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 6, "A");
    inf.readSpace();
    inf.readInt(1, 6, "B");
    inf.readEoln();

    inf.readInt(1, 6, "C");
    inf.readSpace();
    inf.readInt(1, 6, "D");
    inf.readEoln();

    inf.readEof();
}
