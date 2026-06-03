#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 1000000, "N");
    inf.readSpace();
    inf.readInt(2, 1000000, "K");
    inf.readEoln();
    inf.readEof();
}
