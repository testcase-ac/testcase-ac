#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 3500, "N");
    inf.readSpace();
    inf.readInt(1, 12, "K");
    inf.readEoln();
    inf.readEof();
}
