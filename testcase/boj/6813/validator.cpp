#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only gives w >= 7; cap w to keep generated output practical.
    int w = inf.readInt(7, 1000000, "w");
    inf.readEoln();
    inf.readEof();

    return 0;
}
