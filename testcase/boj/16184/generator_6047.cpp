#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll LIM = 1000000000000000000LL;
    // prepare powers of two up to 1e18
    vector<ll> p2;
    for (int k = 0; k <= 60; ++k) {
        ll v = (1LL << k);
        if (v >= 1 && v <= LIM) p2.push_back(v);
    }
    // prepare p2-1 for p2 > 1
    vector<ll> p2m1;
    for (ll v : p2) if (v > 1) p2m1.push_back(v - 1);

    // number of test cases
    int T = 10;
    vector<ll> Ns;
    Ns.reserve(T);

    // small edge cases
    Ns.push_back(1);
    Ns.push_back(2);
    Ns.push_back(rnd.next(3LL, 4LL));
    // exact powers of two
    Ns.push_back(rnd.any(p2));
    // one less than power of two
    Ns.push_back(rnd.any(p2m1));
    // small random (5 to 10)
    Ns.push_back(rnd.next(5LL, 10LL));
    // moderate (11 to 100)
    Ns.push_back(rnd.next(11LL, 100LL));
    // larger random (1e3 to 1e6)
    Ns.push_back(rnd.next(1000LL, 1000000LL));
    // medium-large (1e9 to 1e12)
    Ns.push_back(rnd.next(1000000000LL, 1000000000000LL));
    // near the maximum: pick 1e18, 1e18-1 or 1e18-2
    vector<ll> nearMax = {LIM, LIM - 1, LIM - 2};
    Ns.push_back(rnd.any(nearMax));

    // shuffle to vary order
    shuffle(Ns.begin(), Ns.end());

    // output
    println(T);
    for (ll n : Ns) println(n);

    return 0;
}
