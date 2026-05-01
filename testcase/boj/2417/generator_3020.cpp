#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = LLONG_MAX;
    const long long MAX_Q = 3037000499LL; // floor(sqrt(2^63-1))

    int caseId = rnd.next(0, 4);
    long long n;
    if (caseId == 0) {
        // Small random n
        n = rnd.next(0LL, 100LL);
    } else if (caseId == 1) {
        // Exact squares
        long long k = (rnd.next() < 0.2
                       ? rnd.next(0LL, 1000LL)
                       : rnd.next(0LL, MAX_Q));
        n = k * k;
    } else if (caseId == 2) {
        // One less than a square
        long long k = (rnd.next() < 0.2
                       ? rnd.next(1LL, 1000LL)
                       : rnd.next(1LL, MAX_Q));
        n = k * k - 1;
    } else if (caseId == 3) {
        // One more than a square
        long long k = (rnd.next() < 0.2
                       ? rnd.next(0LL, 999LL)
                       : rnd.next(0LL, MAX_Q - 1LL));
        n = k * k + 1;
    } else {
        // Near the upper bound of 2^63-1
        long long off = rnd.next(0LL, 10LL);
        n = MAX_N - off;
    }

    println(n);
    return 0;
}
