#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K, H, Q
    int K = inf.readInt(1, 50, "K");
    inf.readSpace();
    int H = inf.readInt(1, 50, "H");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Compute M = (K+1)^H - 1, ensure it fits in <= 1e18
    const __int128 LIMIT = (__int128)1000000000000000000LL + 1; // we need (K+1)^H <= 1e18+1
    __int128 cur = 1;
    for (int i = 1; i <= H; i++) {
        // before multiplying, ensure no overflow beyond LIMIT
        __int128 factor = (__int128)(K + 1);
        ensuref(cur <= LIMIT / factor,
                "Overflow when computing (K+1)^H at step %d: current value %lld too large for multiply by %d",
                i, (long long)cur, K + 1);
        cur *= factor;
    }
    // Now cur = (K+1)^H, enforce that cur-1 <= 1e18
    ensuref(cur - 1 <= (__int128)1000000000000000000LL,
            "(K+1)^H - 1 must be <= 1e18, but got %lld", (long long)(cur - 1));
    long long M = (long long)(cur - 1);

    // Read queries
    for (int i = 1; i <= Q; i++) {
        long long A = inf.readLong(1LL, 1000000000000000000LL, "A_i");
        inf.readSpace();
        long long B = inf.readLong(1LL, 1000000000000000000LL, "B_i");
        inf.readEoln();
        ensuref(A <= B,
                "Query %d invalid: A (%lld) > B (%lld)", i, A, B);
    }

    inf.readEof();
    return 0;
}
