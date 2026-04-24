#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small primes for constructing diverse N
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    // Choose a category for N
    // 0 -> N = 1
    // 1 -> small prime
    // 2 -> product of two distinct small primes
    // 3 -> square of a small prime
    // 4 -> random N in [2,30]
    int category = rnd.next(0, 4);
    int N;
    if (category == 0) {
        N = 1;
    } else if (category == 1) {
        // pick a small prime
        N = rnd.any(primes);
    } else if (category == 2) {
        // pick two distinct primes and multiply
        shuffle(primes.begin(), primes.end());
        N = primes[0] * primes[1];
    } else if (category == 3) {
        // pick one prime and square it
        int p = rnd.any(primes);
        N = p * p;
    } else {
        // completely random small N
        N = rnd.next(2, 30);
    }

    // Ensure N does not exceed 1e9
    if (N > 1000000000) N = 1000000000;

    // Output a single N
    println(N);

    return 0;
}
