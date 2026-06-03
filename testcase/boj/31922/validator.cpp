#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 500, "A");
    inf.readSpace();
    inf.readInt(1, 500, "P");
    inf.readSpace();
    inf.readInt(1, 500, "C");
    inf.readEoln();
    inf.readEof();
}
