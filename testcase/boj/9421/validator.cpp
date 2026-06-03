#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(10, 1000000, "n");
    inf.readEoln();
    inf.readEof();
}
