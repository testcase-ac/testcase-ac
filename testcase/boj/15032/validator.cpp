#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 400, "N");
    inf.readSpace();
    inf.readInt(1, 400, "K");
    inf.readEoln();
    inf.readEof();
}
