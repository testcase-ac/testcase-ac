#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(6, 10);
    vector<pair<int, ll>> cases;
    // Corner cases
    cases.emplace_back(1, 1LL);
    cases.emplace_back(1, 1000000000LL);
    cases.emplace_back(10000, 1LL);
    cases.emplace_back(10000, 1000000000LL);
    int extra = T - (int)cases.size();
    for (int i = 0; i < extra; ++i) {
        int N;
        int pickN = rnd.next(0, 4);
        if (pickN == 0) N = 1;
        else if (pickN == 1) N = 10000;
        else N = rnd.next(2, 9999);
        int regime = rnd.next(0, 3);
        ll S;
        if (regime == 0) {
            // Small S < N+1
            ll lo = 1;
            ll hi = min<ll>(N, 100LL);
            S = rnd.next(lo, hi);
        } else if (regime == 1) {
            // Exactly divisible by N+1
            ll m = (ll)N + 1;
            ll maxk = 1000000000LL / m;
            ll lo = 1;
            ll hi = min<ll>(maxk, 1000LL);
            ll k = rnd.next(lo, hi);
            S = k * m;
        } else if (regime == 2) {
            // Around N+1
            vector<int> deltas = {-1, 0, 1};
            int d = rnd.any(deltas);
            ll val = (ll)N + 1 + d;
            if (val < 1) val = 1;
            if (val > 1000000000LL) val = 1000000000LL;
            S = val;
        } else {
            // Fully random
            ll lo = 1;
            ll hi = 1000000000LL;
            S = rnd.next(lo, hi);
        }
        cases.emplace_back(N, S);
    }
    shuffle(cases.begin(), cases.end());
    for (auto &p : cases) {
        println(p.first, p.second);
    }
    return 0;
}
