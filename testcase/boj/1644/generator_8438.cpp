#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Prepare prime lists for hyper-parameter sampling
    vector<int> small_primes = {
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    vector<int> large_primes = {
        999983, 1000003, 1000033, 1000037, 1000039
    };

    // Choose a category to diversify N
    int cat = rnd.next(1, 5);
    int N;
    switch (cat) {
        // Very small N, includes edge cases 1..10
        case 1:
            N = rnd.next(1, 10);
            break;
        // Small-to-medium N
        case 2:
            N = rnd.next(11, 1000);
            break;
        // Medium-to-large N
        case 3:
            N = rnd.next(1001, 1000000);
            break;
        // Near the upper constraint
        case 4:
            N = rnd.next(4000000 - 1000, 4000000);
            break;
        // Specifically primes to test prime-edge behaviors
        case 5:
            if (rnd.next(0, 1))
                N = rnd.any(small_primes);
            else
                N = rnd.any(large_primes);
            break;
        default:
            N = rnd.next(1, 4000000);
    }

    // Output the single test case
    println(N);

    return 0;
}
