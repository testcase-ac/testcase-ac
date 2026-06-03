#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 200000000, "K");
    inf.readSpace();
    inf.readInt(1, 200000000, "N");
    inf.readEoln();
    inf.readEof();
}
