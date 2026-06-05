#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 2000000000, "S");
    inf.readEoln();
    inf.readEof();
}
