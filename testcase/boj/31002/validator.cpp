#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(3, 100000, "N");
    inf.readSpace();
    inf.readInt(0, 100000, "K");
    inf.readEoln();
    inf.readEof();
}
