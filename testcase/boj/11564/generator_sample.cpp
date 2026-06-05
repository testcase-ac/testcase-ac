#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const ll LIM = 1000000000000000000LL;

ll valueNear(ll base, ll radius) {
    ll lo = max(-LIM, base - radius);
    ll hi = min(LIM, base + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    ll k = 1;
    ll a = 0;
    ll b = 0;
    int mode = rnd.next(8);

    if (mode == 0) {
        k = rnd.next(1LL, 20LL);
        a = -rnd.next(0LL, 100LL);
        b = rnd.next(0LL, 100LL);
    } else if (mode == 1) {
        k = rnd.next(1LL, 1000LL);
        a = rnd.next(1LL, 100000LL);
        b = rnd.next(a, min(LIM, a + rnd.next(0LL, 100000LL)));
    } else if (mode == 2) {
        k = rnd.next(1LL, 1000LL);
        b = -rnd.next(1LL, 100000LL);
        a = rnd.next(max(-LIM, b - rnd.next(0LL, 100000LL)), b);
    } else if (mode == 3) {
        k = rnd.next(1LL, LIM);
        a = rnd.next(-1000LL, 1000LL);
        b = a;
    } else if (mode == 4) {
        k = rnd.next(1LL, 1000000000LL);
        ll m = rnd.next(-1000000LL, 1000000LL);
        ll center = m * k;
        a = valueNear(center, k);
        b = valueNear(center, k);
        if (a > b) swap(a, b);
    } else if (mode == 5) {
        k = rnd.next(1LL, LIM);
        a = rnd.any(vector<ll>{-LIM, -LIM + rnd.next(0LL, 1000LL), 0LL});
        b = rnd.any(vector<ll>{0LL, LIM - rnd.next(0LL, 1000LL), LIM});
        if (a > b) swap(a, b);
    } else if (mode == 6) {
        k = rnd.next(1000000000000LL, LIM);
        a = rnd.next(-LIM, LIM);
        b = rnd.next(a, LIM);
    } else {
        k = rnd.next(1LL, 1000000LL);
        ll len = rnd.next(0LL, 1000000LL);
        a = rnd.next(-1000000000LL, 1000000000LL);
        b = a + len;
    }

    println(k, a, b);
    return 0;
}
