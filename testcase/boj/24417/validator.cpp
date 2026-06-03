#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(5, 200000000, "n");
    inf.readEoln();
    inf.readEof();
}
