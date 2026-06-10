#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 999999999, "n");
    inf.readEoln();
    inf.readEof();
}
