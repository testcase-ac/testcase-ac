#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read length of the sequence
    int N = inf.readInt(3, 50, "N");
    inf.readEoln();

    // Read the sequence elements
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = inf.readLong(1LL, 1000000LL, "a_i");
        inf.readEoln();
    }

    // Check if it's an arithmetic progression (AP)
    bool isAP = true;
    long long d = a[1] - a[0];
    for (int i = 2; i < N; i++) {
        if (a[i] - a[i-1] != d) {
            isAP = false;
            break;
        }
    }

    // Check if it's a geometric progression (GP)
    bool isGP = true;
    long long r = 0;
    // Since all a[i] >= 1, division by a[0] is safe
    if (a[1] % a[0] != 0) {
        isGP = false;
    } else {
        r = a[1] / a[0];
        for (int i = 2; i < N; i++) {
            // Check exact multiplication
            // Use __int128 to avoid overflow in intermediate
            __int128 prod = __int128(a[i-1]) * __int128(r);
            if (prod != a[i]) {
                isGP = false;
                break;
            }
        }
    }

    // The problem guarantees the sequence is either AP or GP
    ensuref(isAP || isGP,
            "Sequence is neither arithmetic nor geometric progression");

    // Compute the next term
    __int128 next128;
    if (isAP) {
        next128 = __int128(a[N-1]) + __int128(d);
    } else {
        next128 = __int128(a[N-1]) * __int128(r);
    }
    // Check next term bounds [1, 2e9]
    ensuref(next128 >= 1 && next128 <= 2000000000LL,
            "Next term %lld is out of allowed bounds [1, 2000000000]", (long long)next128);

    inf.readEof();
    return 0;
}
