#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is only one line, with 10 integers, each in [1,5], separated by spaces, then EOLN, then EOF.

    const int N = 10;
    inf.readInts(N, 1, 5, "dice"); // reads 10 ints in [1,5], space separated, no trailing space
    inf.readEoln();
    inf.readEof();
}
