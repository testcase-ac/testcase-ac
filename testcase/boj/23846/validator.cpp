#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 3000, "N");
    inf.readSpace();
    inf.readInt(1, 456, "K");
    inf.readEoln();
    inf.readEof();
}
