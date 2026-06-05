#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "A");
    inf.readSpace();
    inf.readInt(1, 1000000, "B");
    inf.readSpace();
    inf.readInt(1, 1000000, "C");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readEoln();
    inf.readEof();
}
