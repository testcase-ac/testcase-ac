#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "A");
    inf.readSpace();
    inf.readInt(1, 100, "B");
    inf.readSpace();
    inf.readInt(1, 100, "C");
    inf.readEoln();
    inf.readEof();
}
