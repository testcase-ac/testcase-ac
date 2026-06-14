#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 500000, "N");
    inf.readEoln();
    inf.readEof();
}
