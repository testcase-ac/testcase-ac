#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m as natural numbers (1 to 10^18)
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
    inf.readEoln();

    // No other global constraints to check for this problem.
    inf.readEof();
    return 0;
}
