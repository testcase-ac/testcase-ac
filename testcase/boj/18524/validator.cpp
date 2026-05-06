#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case, one line: m k
    long long m = inf.readLong(1LL, 1000000LL, "m");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000LL, "k");
    inf.readEoln();

    // No further structural/global constraints to check:
    // - m, k are simple integers in the specified range
    // - Output constraints (mod prime, etc.) are for the solution, not validator

    inf.readEof();
}
