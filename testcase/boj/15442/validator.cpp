#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 30, "N");
    inf.readSpace();
    inf.readInt(1, 900, "K");
    inf.readEoln();
    inf.readEof();

    return 0;
}
