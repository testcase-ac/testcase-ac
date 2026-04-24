#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two integers A and B in [1, 1e6], separated by exactly one space, then newline, then EOF.
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000000, "B");
    inf.readEoln();
    inf.readEof();

    return 0;
}
