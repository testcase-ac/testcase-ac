#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

pair<ll, ll> makeInterval(ll low, ll high, int mode) {
    if (mode == 0) {
        ll l = rnd.next(low, high - 1);
        ll r = rnd.next(l + 1, min(high, l + rnd.next(1LL, 8LL)));
        return {l, r};
    }

    if (mode == 1) {
        ll center = rnd.next(low + 2, high - 2);
        ll l = rnd.next(low, center - 1);
        ll r = rnd.next(center + 1, high);
        return {l, r};
    }

    if (mode == 2) {
        ll start = rnd.next(low, high - 3);
        ll len = rnd.next(1LL, min(12LL, high - start));
        return {start, start + len};
    }

    ll l = rnd.next(low, high - 1);
    ll r = rnd.next(l + 1, high);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, 24);
        ll c;
        if (mode == 4) {
            c = rnd.next(1000000000000000LL, 1000000000000000000LL);
        } else if (rnd.next(0, 3) == 0) {
            c = rnd.next(1LL, 3LL);
        } else {
            c = rnd.next(1LL, 100LL);
        }

        println(n, c);

        ll low = 1;
        ll high = rnd.next(12LL, 80LL);
        if (mode == 4) {
            low = rnd.next(9999999999900LL, 9999999999990LL);
            high = 10000000000000LL;
        }

        vector<pair<ll, ll>> intervals;
        intervals.reserve(n);

        if (mode == 3) {
            ll cursor = low;
            for (int i = 0; i < n; ++i) {
                ll len = rnd.next(1LL, 6LL);
                ll gap = rnd.next(0LL, 3LL);
                ll l = min(cursor, 9999999999999LL);
                ll r = min(10000000000000LL, l + len);
                intervals.push_back({l, r});
                cursor = r + gap;
            }
        } else {
            int pattern = rnd.next(0, 3);
            for (int i = 0; i < n; ++i) {
                if (!intervals.empty() && rnd.next(0, 4) == 0) {
                    intervals.push_back(rnd.any(intervals));
                } else {
                    intervals.push_back(makeInterval(low, high, pattern));
                }
            }
        }

        shuffle(intervals.begin(), intervals.end());
        for (auto interval : intervals) {
            println(interval.first, interval.second);
        }
    }

    return 0;
}
