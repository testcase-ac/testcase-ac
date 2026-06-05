#include "testlib.h"
#include <vector>

using ll = long long;
using std::vector;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_VALUE = 1000000000000000000LL;
    const vector<ll> smallBases = {1LL, 2LL, 3LL, 10LL, 100LL, 1000LL};
    const vector<ll> exponents = {1LL, 2LL, 10LL, 60LL, 1000LL, MAX_VALUE};
    const vector<ll> moduli = {1LL, 2LL, 3LL, 10LL, 1000000007LL, MAX_VALUE};

    ll a = 1;
    ll b = 1;
    ll c = 1;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        a = rnd.next(1LL, 30LL);
        b = rnd.next(1LL, 30LL);
        c = rnd.next(1LL, 100LL);
    } else if (mode == 1) {
        a = rnd.any(smallBases);
        b = rnd.any(exponents);
        c = rnd.next(1LL, 1000000LL);
    } else if (mode == 2) {
        a = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
        b = rnd.next(1LL, 1000000LL);
        c = rnd.next(1LL, 1000000LL);
    } else if (mode == 3) {
        a = rnd.next(1LL, 1000000LL);
        b = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
        c = rnd.next(1LL, 1000000LL);
    } else if (mode == 4) {
        a = rnd.next(1LL, MAX_VALUE);
        b = rnd.next(1LL, MAX_VALUE);
        c = rnd.any(moduli);
    } else {
        a = rnd.next(1LL, MAX_VALUE);
        b = rnd.next(1LL, MAX_VALUE);
        c = rnd.next(1LL, MAX_VALUE);
    }

    println(a, b, c);
    return 0;
}
