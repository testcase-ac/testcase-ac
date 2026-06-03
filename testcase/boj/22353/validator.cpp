#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "a");
    inf.readSpace();
    inf.readInt(1, 100, "d");
    inf.readSpace();
    inf.readInt(1, 100, "k");
    inf.readEoln();
    inf.readEof();
}
