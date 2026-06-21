#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 50, "k");
    inf.readEoln();

    inf.readInt(1, 100, "p");
    inf.readSpace();
    inf.readInt(1, 100, "q");
    inf.readSpace();
    inf.readInt(1, 100, "r");
    inf.readSpace();
    inf.readInt(1, 100, "s");
    inf.readEoln();

    inf.readInt(1, 10, "a_1");
    inf.readEoln();

    inf.readEof();
}
