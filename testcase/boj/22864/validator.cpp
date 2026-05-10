#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read four integers: A, B, C, M
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 10000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 10000, "C");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
