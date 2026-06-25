#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only prints upper bounds. M and k are positive
    // because they are a denominator limit and a 1-indexed rank.
    inf.readInt(1, 30000, "M");
    inf.readSpace();
    inf.readInt(1, 200000, "k");
    inf.readEoln();
    inf.readEof();
}
