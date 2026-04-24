#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input consists of exactly 10 lines, each with 10 integers (0 or 1).
    for (int i = 0; i < 10; i++) {
        // Read exactly 10 integers in [0,1]
        inf.readInts(10, 0, 1, "cell");
        // After reading 10 tokens, there must be exactly one end-of-line
        inf.readEoln();
    }

    // No extra data after the 10 lines
    inf.readEof();
    return 0;
}
