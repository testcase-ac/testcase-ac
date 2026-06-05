#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 20, "n");
    inf.readEoln();

    inf.readInt(1, 10, "p");
    inf.readSpace();
    inf.readInt(1, 10, "q");
    inf.readSpace();
    inf.readInt(1, 10, "r");
    inf.readSpace();
    inf.readInt(1, 10, "s");
    inf.readEoln();

    inf.readInt(1, 100, "a_1");
    inf.readEoln();

    inf.readEof();
}
