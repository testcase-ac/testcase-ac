#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;
using ui64 = uint64_t;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Array size hyper-parameter
    int n = rnd.next(1, 12);
    // Prepare the array initialized to 1
    vector<ui64> a(n, 1);
    // A small set of primes for factor segments
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    // Number of segments to apply
    int segCount = rnd.next(1, n);
    for (int it = 0; it < segCount; ++it) {
        // Choose a prime, unbiased
        int p = rnd.any(primes);
        // Choose segment start
        int l = rnd.next(1, n);
        // Biased segment length: small, medium, or large
        int bias = rnd.next(-1, 1);
        int maxLen = n - l + 1;
        int len = rnd.wnext(maxLen, bias) + 1;  // in [1..maxLen]
        int r = l + len - 1;
        // Multiply each in [l-1..r-1] by p
        for (int i = l - 1; i < r; ++i) {
            a[i] *= p;
        }
    }
    // Output the test case
    println(n);
    println(a);
    return 0;
}
