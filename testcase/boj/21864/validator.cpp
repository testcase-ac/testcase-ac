#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 2000000, "n");
    inf.readEoln();
    inf.readEof();
}
