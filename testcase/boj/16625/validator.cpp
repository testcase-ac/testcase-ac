#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "p");
    inf.readSpace();
    inf.readInt(1, 100, "q");
    inf.readSpace();
    inf.readInt(1, 10000, "s");
    inf.readEoln();
    inf.readEof();
}
