#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<ll, ll>> cases;
    int targetT = rnd.next(20, 100);

    auto addCase = [&](ll n, ll k) {
        n = max(1LL, min(1000000000LL, n));
        k = max(1LL, min(1000000000LL, k));
        cases.push_back({n, k});
    };

    auto addYes = [&](ll a, ll b) {
        addCase(a + b - 1, a * b);
    };

    addCase(1, 1);
    addCase(2, 1);
    addCase(3, 4);
    addCase(15, 1);
    addCase(5, 5);
    addYes(1, rnd.next(1, 1000000000));
    addYes(rnd.next(1, 31623), rnd.next(1, 31623));
    addCase(1000000000LL, 1000000000LL);
    addCase(999999999LL, 1);

    while ((int)cases.size() < targetT) {
        int mode = rnd.next(7);

        if (mode == 0) {
            ll a = rnd.next(1, 1000);
            ll b = rnd.next(1, 1000);
            addYes(a, b);
        } else if (mode == 1) {
            ll a = rnd.next(1, 31623);
            ll b = rnd.next(1LL, 1000000000LL / a);
            addYes(a, b);
        } else if (mode == 2) {
            ll a = rnd.next(1, 100000);
            ll b = rnd.next(1LL, 1000000000LL / a);
            ll n = a + b - 1;
            ll delta = rnd.any(vector<ll>{-2, -1, 1, 2});
            addCase(n + delta, a * b);
        } else if (mode == 3) {
            ll n = rnd.next(1, 200);
            ll k = rnd.next(1, 200);
            addCase(n, k);
        } else if (mode == 4) {
            ll n = rnd.next(1, 1000000000);
            ll k = rnd.next(1, 1000000000);
            addCase(n, k);
        } else if (mode == 5) {
            ll n = rnd.next(1, 1000000000);
            ll k = rnd.any(vector<ll>{1LL, 2LL, 3LL, 4LL, 999999937LL, 1000000000LL});
            addCase(n, k);
        } else {
            ll side = rnd.next(1, 31623);
            ll offset = rnd.next(-3, 3);
            addCase(2 * side - 1 + offset, side * side);
        }
    }

    shuffle(cases.begin(), cases.end());
    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
