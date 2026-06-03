#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 4, "A");
    inf.readSpace();
    inf.readInt(1, 4, "B");
    inf.readEoln();
    inf.readEof();
}
