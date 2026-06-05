#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(3, 2000000, "N");
    inf.readEoln();
    inf.readEof();
}
