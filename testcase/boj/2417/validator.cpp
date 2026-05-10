#include "testlib.h"
#include <climits>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n: 0 ≤ n < 2^63
    long long n = inf.readLong(0LL, LLONG_MAX, "n");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
