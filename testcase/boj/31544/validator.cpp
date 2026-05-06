#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: three integers N, M, K
    long long N = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000LL, "M");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000LL, "K");
    inf.readEoln();

    // Problem states K is a divisor of N
    ensuref(N % K == 0, "K must be a divisor of N, but N = %lld, K = %lld", N, K);

    // No further global conditions implied (answer always exists for any valid N,M,K)

    inf.readEof();
}
