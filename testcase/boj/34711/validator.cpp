#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N: number of buildings
    // Constraint: 1 <= N <= 1e12
    long long N = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();

    // No further structure to validate; N is the only input.
    // Canonical form, range, and final newline are already enforced.

    inf.readEof();
}
