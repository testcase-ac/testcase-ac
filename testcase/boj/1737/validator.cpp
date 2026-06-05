#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the Korean BOJ statement for this local problem gives one natural
    // number n, while a legacy English variant describes multiple real inputs
    // ending at -1. The repository's problem data and official sample follow
    // the Korean single-integer contract.
    inf.readInt(1, 1000, "n");
    inf.readEoln();
    inf.readEof();
}
