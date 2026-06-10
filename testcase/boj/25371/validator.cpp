#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "n");
    inf.readSpace();
    inf.readInt(2, 10, "k");
    inf.readEoln();
    inf.readEof();
}
