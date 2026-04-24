#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and G, each between 1 and 1e9 inclusive
    long long R = inf.readLong(1LL, 1000000000LL, "R");
    inf.readSpace();
    long long G = inf.readLong(1LL, 1000000000LL, "G");
    inf.readEoln();

    // No further constraints on R and G beyond their ranges.
    // Every valid input has at least one distribution (N=1), so no need to check existence of solutions.

    inf.readEof();
    return 0;
}
