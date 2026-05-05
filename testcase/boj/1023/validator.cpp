#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    // Compute maximum allowed K = 2^N - 1
    // N <= 50, so (1LL << N) is safe in 64-bit
    long long maxK = (N < 63 ? ((1LL << N) - 1) : LLONG_MAX);
    // Read K with dynamic upper bound
    long long K = inf.readLong(0LL, maxK, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
