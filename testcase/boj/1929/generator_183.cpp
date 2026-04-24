#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // List of small primes to guarantee at least one in the range
    vector<int> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    int P = rnd.any(smallPrimes);

    // Hyper-parameter: tParam controls distribution of width
    int tParam = rnd.next(1, 3);
    if (rnd.next(0, 1)) tParam = -tParam;
    int width = rnd.wnext(20, tParam);
    if (width < 1) width = 1;

    // Ensure M ≤ P ≤ N and within [1, 1e6]
    int M_lo = max(1, P - width);
    int M = rnd.next(M_lo, P);
    int N_hi = min(1000000, P + width);
    int N = rnd.next(P, N_hi);

    // Output a valid input with at least one prime in [M, N]
    println(M, N);
    return 0;
}
