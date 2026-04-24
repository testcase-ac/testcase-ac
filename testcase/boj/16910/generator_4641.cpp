#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of queries small
    int N = rnd.next(1, 15);

    // Upper bound for values: sometimes small, sometimes large
    vector<ll> bounds = {10LL, 1000LL, 1000000000000000000LL};
    ll B = rnd.any(bounds);

    // Possible delta ranges for intervals
    vector<ll> deltas = {0, 1, 5, 100, B - 1};

    println(N);
    for (int i = 0; i < N; i++) {
        // Query type: 1 to 3 with variable bias
        int t = rnd.next(-1, 1);
        int q = rnd.wnext(3, t) + 1;

        // Choose l and r
        ll d = rnd.any(deltas);
        ll l = rnd.next(1LL, B);
        ll maxAdd = B - l;
        ll add = d > maxAdd ? rnd.next(0LL, maxAdd) : rnd.next(0LL, d);
        ll r = l + add;

        println(q, l, r);
    }
    return 0;
}
