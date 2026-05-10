#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: L, N, K
    long long L = inf.readLong(1LL, 1000000000000000000LL, "L");
    inf.readSpace();
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 500000, "K");
    inf.readEoln();

    // K cannot exceed L+1
    // Use 128-bit to avoid overflow
    __int128_t Lp1 = (__int128_t)L + 1;
    ensuref((__int128_t)K <= Lp1,
            "K (%d) must be <= L+1 (%lld)", K, (long long)Lp1);

    // Read the positions A_1 ... A_N
    vector<long long> A = inf.readLongs(N, 0LL, L, "A_i");
    inf.readEoln();

    // Check strictly increasing A_i
    for (int i = 1; i < N; i++) {
        ensuref(A[i] > A[i-1],
                "A[%d] = %lld must be greater than A[%d] = %lld",
                i, A[i], i-1, A[i-1]);
    }

    inf.readEof();
    return 0;
}
