#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute powers of two up to 1e18
    vector<ll> pow2;
    for (ll v = 1; v <= 1000000000000000000LL; v <<= 1)
        pow2.push_back(v);

    int scenario = rnd.next(1, 7);
    ll k = 1;
    switch (scenario) {
        case 1:
            // Very small edge: [1,3]
            k = rnd.next(1LL, 3LL);
            break;
        case 2:
            // Small random: [1,10]
            k = rnd.next(1LL, 10LL);
            break;
        case 3:
            // Medium random: [1, 1e6]
            k = rnd.next(1LL, 1000000LL);
            break;
        case 4:
            // Larger random: [1e6, 1e12]
            k = rnd.next(1000000LL, 1000000000000LL);
            break;
        case 5:
            // Max boundary
            k = 1000000000000000000LL;
            break;
        case 6:
            // Exact power of two
            k = rnd.any(pow2);
            break;
        case 7: {
            // Near a power of two (± small delta)
            ll base = rnd.any(pow2);
            ll delta;
            if (base <= 1) {
                delta = 1;
                k = base + delta;
            } else {
                delta = rnd.next(1LL, min(base - 1, 10LL));
                if (rnd.next(0, 1) == 0) k = base + delta;
                else k = base - delta;
            }
            break;
        }
    }
    // Clamp just in case
    k = max(1LL, min(k, 1000000000000000000LL));
    println(k);
    return 0;
}
