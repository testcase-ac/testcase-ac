#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of matrices
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    vector<int> r(N), c(N);
    for (int i = 0; i < N; ++i) {
        r[i] = inf.readInt(1, 10000, "r_i");
        inf.readSpace();
        c[i] = inf.readInt(1, 10000, "c_i");
        inf.readEoln();
    }

    // Check that multiplication in the given order is always possible:
    // For all i, c[i] == r[i+1]
    for (int i = 0; i + 1 < N; ++i) {
        ensuref(c[i] == r[i + 1],
                "Incompatible matrix dimensions at position %d and %d: c[%d]=%d, r[%d]=%d",
                i + 1, i + 2, i + 1, c[i], i + 2, r[i + 1]);
    }

    // The statement guarantees:
    // - There exists an order with total multiplications <= 2^63 - 1
    // - The worst order also has total multiplications <= 2^63 - 1
    //
    // The worst order is simply left-to-right ((A1A2)A3)...AN,
    // since this corresponds to parenthesization that is fixed.
    // We must verify that even this sequence does not overflow 2^63 - 1.
    //
    // Perform the left-to-right multiplication and count operations
    // using __int128 to avoid overflow during intermediate computations.

    const long long LIM = (1LL << 63) - 1;
    __int128 ops = 0;
    long long cur_r = r[0];
    long long cur_c = c[0];

    for (int i = 1; i < N; ++i) {
        long long nr = r[i];
        long long nc = c[i];
        // cur matrix: cur_r x cur_c, next: nr x nc, with cur_c == nr
        __int128 add = (__int128)cur_r * (__int128)cur_c * (__int128)nc;
        ensuref(add >= 0, "Negative operation count encountered (should be impossible)");

        ops += add;
        ensuref(ops <= (__int128)LIM,
                "Total multiplications in left-to-right order exceed 2^63-1");

        // Update current matrix dimension after multiplication
        cur_c = nc;
    }

    // Because all dimensions are positive, ops == 0 only when N == 1
    // In that case the "minimum number of multiplications" is 0,
    // which is not a natural number, but the statement only constrains
    // that the answer (if non-zero) is <= 2^63-1. This is consistent.

    inf.readEof();
}
