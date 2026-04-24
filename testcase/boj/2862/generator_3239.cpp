#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a category for diversity
    // 0: small random [2,10]
    // 1: medium random [11,20]
    // 2: near (2^k - 1)
    // 3: exact power of two (2^k)
    int cat = rnd.next(0, 3);
    long long N;
    if (cat == 0) {
        N = rnd.next(2LL, 10LL);
    } else if (cat == 1) {
        N = rnd.next(11LL, 20LL);
    } else if (cat == 2) {
        int k = rnd.next(2, 5);
        N = (1LL << k) - 1;
    } else {
        int k = rnd.next(2, 6);
        N = (1LL << k);
    }

    // Occasionally pick a very large N near the upper limits
    if (rnd.next(0, 9) == 0) {
        vector<long long> specials = {1000000000000000LL, 1000000000000LL, 1000000000000000LL - 1};
        N = rnd.any(specials);
    }

    // Ensure N is within [2, 1e15]
    N = max(2LL, min(N, 1000000000000000LL));

    // Output the single test case
    println(N);

    return 0;
}
