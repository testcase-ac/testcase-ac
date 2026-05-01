#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate d: even, between 2 and 4000, with varied sizes
    int r = rnd.next(1, 100);
    int half_d;
    if (r <= 10) {
        // smallest case
        half_d = 1;               // d = 2
    } else if (r <= 40) {
        // small cases
        half_d = rnd.next(2, 50); // d in [4,100]
    } else if (r <= 70) {
        // medium cases
        half_d = rnd.next(51, 500); // d in [102,1000]
    } else {
        // large cases
        half_d = rnd.next(501, 2000); // d in [1002,4000]
    }
    int d = half_d * 2;

    // Generate m: a prime in [2, 2e9], choose from predefined lists
    vector<int> small_primes = {2, 3, 5, 7, 97, 101, 127, 131, 1009, 10007, 1000003, 19260817};
    vector<int> large_primes = {998244353, 1000000007, 1000000009, 1004535809, 1045430273, 1610612741, 1999999973};
    int m;
    if (rnd.next(1, 100) <= 40) {
        m = rnd.any(small_primes);
    } else {
        m = rnd.any(large_primes);
    }

    // Output a single test case
    println(d, m);

    return 0;
}
