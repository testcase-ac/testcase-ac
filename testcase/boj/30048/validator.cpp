#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 500, "N");
    inf.readSpace();
    inf.readInt(0, 500, "E");
    inf.readEoln();
    inf.readEof();
}
