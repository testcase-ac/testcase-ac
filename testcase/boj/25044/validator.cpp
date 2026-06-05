#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "N");
    inf.readSpace();
    inf.readInt(0, 59, "K");
    inf.readEoln();
    inf.readEof();
}
