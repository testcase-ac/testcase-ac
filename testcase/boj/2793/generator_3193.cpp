#include "testlib.h"
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Upper constraint
    const ll MAXN = 100000000000000000LL; // 1e17

    // Hyper-parameter: range length L between 1 and 20
    ll L = rnd.next(1, 20);

    // Decide small or large A for diversity
    bool smallCase = rnd.next() < 0.7;
    ll A;
    if (smallCase) {
        // small A in [3, 100-L]
        ll upper = max(3LL, 100LL - L);
        A = rnd.next(3LL, upper);
    } else {
        // large A near the upper bound
        ll start = MAXN - 10000 - L;
        ll end   = MAXN - 1 - L;
        A = rnd.next(start, end);
    }
    ll B = A + L;  // ensure A < B and B < 1e17

    // Output single test case
    println(A, B);
    return 0;
}
