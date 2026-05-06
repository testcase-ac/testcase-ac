#include "testlib.h"
#include <limits>
using namespace std;

static long long safe_gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two positive integers A and B on one line
    long long A = inf.readLong(1LL, 100000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 100000000LL, "B");
    inf.readEoln();

    // Validate that their LCM fits in a signed 64-bit integer
    long long g = safe_gcd(A, B);
    __int128 lcm = (__int128)A / g * B;
    ensuref(lcm <= numeric_limits<long long>::max(),
            "LCM of A=%lld and B=%lld is too large: %lld", 
            A, B, (long long)lcm);

    inf.readEof();
    return 0;
}
