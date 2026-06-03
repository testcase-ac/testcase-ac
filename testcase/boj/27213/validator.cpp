#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000000, "m");
    inf.readEoln();
    inf.readInt(1, 100000000, "n");
    inf.readEoln();
    inf.readEof();
}
