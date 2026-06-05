#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 100, "A");
    inf.readSpace();
    inf.readInt(1, 100, "B");
    inf.readEoln();
    inf.readEof();
}
