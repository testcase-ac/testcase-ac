#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read four non-negative integers a, b, c, d in [0, 1e9].
    long long a = inf.readLong(0LL, 1000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(0LL, 1000000000LL, "b");
    inf.readSpace();
    long long c = inf.readLong(0LL, 1000000000LL, "c");
    inf.readSpace();
    long long d = inf.readLong(0LL, 1000000000LL, "d");
    inf.readEoln();

    // No other global constraints to check for the input.
    inf.readEof();
    return 0;
}
