#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small list of primes >=3
    vector<int> smallPrimes = {3,5,7,11,13,17,19,23,29};
    // Large prime near 2^31-1
    const long long BIGP = 2147483647LL;
    // Number of test cases (lines), no header
    int T = rnd.next(5, 15);
    for (int i = 0; i < T; i++) {
        int tp = rnd.next(0, 4);
        long long N;
        if (tp == 0) {
            // Small N
            N = rnd.next(3, 10);
        } else if (tp == 1) {
            // Prime: small or big
            if (rnd.next(0,1) == 0) N = rnd.any(smallPrimes);
            else N = BIGP;
        } else if (tp == 2) {
            // Power of two
            int e = rnd.next(2, 30);
            N = 1LL << e;
        } else if (tp == 3) {
            // Small prime power
            int p = rnd.any(smallPrimes);
            int e = rnd.next(2, 5);
            long long val = 1;
            for (int j = 0; j < e; j++) {
                val *= p;
                if (val >= (1LL<<31)) break;
            }
            if (val >= (1LL<<31) || val < 3) {
                // fallback to small range
                val = rnd.next(3, 100);
            }
            N = val;
        } else {
            // Random composite or any
            N = rnd.next(3, 1000000000);
        }
        // Ensure N >= 3 and < 2^31
        if (N < 3) N = 3;
        if (N >= (1LL<<31)) N = BIGP;
        println(N);
    }
    return 0;
}
