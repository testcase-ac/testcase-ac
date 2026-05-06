#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers N and M
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000000LL, "M");
    inf.readEoln();

    // No further global properties are implied in the statement:
    // - f(x) = N / x (integer division), always defined for x >= 1
    // - g(x) = x % M, always defined for M >= 1
    // The statement does not guarantee any extra property about the answer
    // (like existence of a bound smaller than trivial), so no simulation
    // or extra checks are needed here.

    inf.readEof();
}
