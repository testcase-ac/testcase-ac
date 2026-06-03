#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000000000, "N");
    inf.readEoln();
    inf.readEof();
}
