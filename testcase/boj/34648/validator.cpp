#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000, "p");
    inf.readSpace();
    inf.readInt(1, 100000, "q");
    inf.readSpace();
    inf.readInt(1, 100000, "n");
    inf.readEoln();
    inf.readEof();
}
