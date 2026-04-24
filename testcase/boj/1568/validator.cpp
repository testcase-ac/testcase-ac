#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of birds N: a natural number, 1 ≤ N ≤ 10^9
    long long N = inf.readLong(1LL, 1000000000LL, "N");

    // There should be exactly one newline after N, then EOF.
    inf.readEoln();
    inf.readEof();

    return 0;
}
