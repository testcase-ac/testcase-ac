#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the integer to be reduced to 1.
    // Constraint from problem: 1 <= N <= 10^6
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();  // Ensure exactly one newline after N

    // No further input
    inf.readEof();
    return 0;
}
