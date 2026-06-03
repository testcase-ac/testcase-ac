#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: fixed testcase normalization represents this no-input problem as one empty line.
    inf.readEoln();
    inf.readEof();
}
