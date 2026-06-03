#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1000, 9999, "X");
    inf.readEoln();
    inf.readEof();
}
