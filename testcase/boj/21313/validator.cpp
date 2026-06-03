#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(4, 1000, "N");
    inf.readEoln();
    inf.readEof();
}
