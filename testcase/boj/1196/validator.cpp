#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers N and K on one line.
    // N: natural number, 1 <= N <= 1e18
    // K: natural number, 1 <= K <= N

    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, N, "K");
    inf.readEoln();

    inf.readEof();
}
