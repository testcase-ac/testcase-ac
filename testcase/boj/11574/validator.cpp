#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 3, "K");
    inf.readEoln();
    inf.readEof();
}
