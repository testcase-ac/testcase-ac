#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: the index of the Fibonacci number to compute.
    // According to the statement, n is a natural number (i.e., >= 1)
    // and at most 10^18.
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readEoln();

    // No further global constraints (connectivity, polygon non‐degeneracy, etc.)
    // are implied by the problem. We simply check the input range.

    inf.readEof();
    return 0;
}
