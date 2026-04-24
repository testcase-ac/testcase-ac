#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two natural numbers between 1 and 10,000,000 inclusive.
    int a = inf.readInt(1, 10000000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10000000, "b");
    inf.readEoln();

    // No further input allowed.
    inf.readEof();
    return 0;
}
