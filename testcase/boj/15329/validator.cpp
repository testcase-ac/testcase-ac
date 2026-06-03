#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "l");
    inf.readSpace();
    inf.readInt(2, 10, "k");
    inf.readEoln();
    inf.readEof();
}
