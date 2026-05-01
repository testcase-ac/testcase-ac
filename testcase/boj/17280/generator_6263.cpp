#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 10);
        int M = rnd.next(0, 10);

        // Generate passenger destinations
        vector<ll> xs;
        for (int i = 0; i < N; ++i) {
            xs.push_back(rnd.next(1, 100));
        }
        shuffle(xs.begin(), xs.end());
        ll minX = *min_element(xs.begin(), xs.end());
        ll maxX = *max_element(xs.begin(), xs.end());

        // Output N, M and passenger list
        println(N, M);
        println(xs);

        // Generate drivers with varied interval types
        vector<pair<ll, ll>> drivers;
        for (int j = 0; j < M; ++j) {
            int tp = rnd.next(0, 3);
            ll y, z;
            if (tp == 0) {
                // Broad interval covering all passengers
                y = 1;
                z = maxX;
            } else if (tp == 1) {
                // Exact-match interval for a random passenger
                ll xpick = rnd.any(xs);
                y = xpick;
                z = xpick;
            } else if (tp == 2) {
                // Random overlapping interval within passenger range
                y = rnd.next(1LL, maxX);
                z = rnd.next(y, maxX);
            } else {
                // Interval that does not overlap any passenger
                bool leftPossible = (minX > 1);
                if (leftPossible && rnd.next(0, 1) == 0) {
                    z = rnd.next(1LL, minX - 1);
                    y = rnd.next(1LL, z);
                } else {
                    ll extra = rnd.next(1, 50);
                    y = rnd.next(maxX + 1, maxX + extra);
                    z = rnd.next(y, maxX + extra);
                }
            }
            drivers.emplace_back(y, z);
        }
        shuffle(drivers.begin(), drivers.end());

        // Output driver intervals
        for (auto &d : drivers) {
            println(d.first, d.second);
        }
    }

    return 0;
}
