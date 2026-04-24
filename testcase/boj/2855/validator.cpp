#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and S
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    long long S = inf.readLong(1LL, 2000000000LL, "S");
    inf.readEoln();

    // Read sequence A of length N, each positive, and total sum ≤ 2e9
    __int128 totalSum = 0;
    for (int i = 0; i < N; i++) {
        long long a = inf.readLong(1LL, 2000000000LL, "A_i");
        totalSum += a;
        inf.readEoln();
    }
    // Check global sum constraint
    ensuref(totalSum <= (__int128)2000000000LL,
            "Total sum of A[1..N] must be ≤ 2e9, found %lld",
            (long long)totalSum);

    inf.readEof();
    return 0;
}
