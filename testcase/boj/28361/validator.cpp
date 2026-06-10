#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(5, 1000000, "N");
    inf.readEoln();
    inf.readEof();
}
