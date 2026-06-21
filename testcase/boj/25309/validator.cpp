#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000000, "N");
    inf.readSpace();
    inf.readInt(1, 10000, "K");
    inf.readEoln();
    inf.readEof();
}
