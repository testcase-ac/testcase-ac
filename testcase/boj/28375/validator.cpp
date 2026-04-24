#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n (1 ≤ n ≤ 1e9).
    long long n = inf.readLong(1LL, 1000000000LL, "n");

    // There should be exactly one newline after n, and then EOF.
    inf.readEoln();
    inf.readEof();

    return 0;
}
