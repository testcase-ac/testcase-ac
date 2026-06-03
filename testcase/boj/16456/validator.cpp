#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 50000, "n");
    inf.readEoln();
    inf.readEof();
}
