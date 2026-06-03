#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 400, "r");
    inf.readSpace();
    inf.readInt(1, 400, "c");
    inf.readEoln();
    inf.readEof();
}
