#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    typedef long long ll;
    const ll MAXV = (ll)1e12;

    vector<pair<ll, ll>> tests;

    // Some fixed edge / interesting cases
    tests.push_back({1, 1});                // smallest
    tests.push_back({1, MAXV});             // minimal health, max food
    tests.push_back({MAXV, 1});             // max health, minimal food
    tests.push_back({7, 1});                // sample
    tests.push_back({8589934591LL, 1});     // sample (2^33 - 1)
    tests.push_back({100, 100});            // equal moderate
    tests.push_back({MAXV, MAXV});          // max equal

    int baseT = (int)tests.size();
    int maxT = 15; // keep output small enough
    int T = rnd.next(baseT, maxT);

    // Precompute powers of two up to MAXV
    vector<ll> p2;
    for (int k = 0; k < 60; k++) {
        ll v = 1LL << k;
        if (v > MAXV) break;
        p2.push_back(v);
    }

    while ((int)tests.size() < T) {
        int type = rnd.next(0, 5);
        ll n = 0, m = 0;

        if (type == 0) {
            // Very small numbers
            n = rnd.next(1LL, 20LL);
            m = rnd.next(1LL, 20LL);
        } else if (type == 1) {
            // Near MAXV, both big
            ll low = MAXV - 1000;
            n = rnd.next(low, MAXV);
            m = rnd.next(low, MAXV);
        } else if (type == 2) {
            // Large disparity
            if (rnd.next(0, 1) == 0) {
                n = rnd.next(1LL, 50LL);
                m = rnd.next((ll)1e11, MAXV);
            } else {
                n = rnd.next((ll)1e11, MAXV);
                m = rnd.next(1LL, 50LL);
            }
        } else if (type == 3) {
            // Around powers of two
            ll base = rnd.any(p2);
            int mode = rnd.next(0, 2); // 0: exact, 1: -1, 2: +1
            if (mode == 1 && base > 1) n = base - 1;
            else if (mode == 2 && base + 1 <= MAXV) n = base + 1;
            else n = base;

            if (rnd.next(0, 1) == 0) {
                m = rnd.next(1LL, 10LL); // small food
            } else {
                // similar scale food
                ll up = min(MAXV, base * 4);
                m = rnd.next(1LL, up);
            }
        } else if (type == 4) {
            // Random moderate
            n = rnd.next(1LL, (ll)1e9);
            m = rnd.next(1LL, (ll)1e9);
        } else {
            // n == m, random size
            if (rnd.next(0, 1) == 0) {
                n = m = rnd.next(1LL, 100LL);
            } else {
                n = m = rnd.next((ll)1e6, MAXV);
            }
        }

        // Ensure within bounds and non-zero (should already be)
        if (n < 1) n = 1;
        if (m < 1) m = 1;
        if (n > MAXV) n = MAXV;
        if (m > MAXV) m = MAXV;

        tests.push_back({n, m});
    }

    println(T);
    for (auto &tc : tests) {
        println(tc.first, tc.second);
    }

    return 0;
}
