#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInts(10, 1, 100, "barn1_bucket");
    inf.readEoln();
    inf.readInts(10, 1, 100, "barn2_bucket");
    inf.readEoln();
    inf.readEof();
}
