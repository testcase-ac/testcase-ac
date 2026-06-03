#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Interval = pair<ll, ll>;

const ll MAX_T = 2100000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 28);
    vector<Interval> intervals;

    if (mode == 0) {
        ll base = rnd.next(0LL, 80LL);
        ll hub = base + rnd.next(5LL, 35LL);
        for (int i = 0; i < n; ++i) {
            ll enter = rnd.next(base, hub);
            ll exit = rnd.next(hub + 1, hub + 45);
            intervals.emplace_back(enter, exit);
        }
    } else if (mode == 1) {
        ll start = rnd.next(0LL, 60LL);
        ll step = rnd.next(1LL, 8LL);
        for (int i = 0; i < n; ++i) {
            ll enter = start + i * step;
            ll exit = enter + rnd.next(1LL, step + 6);
            intervals.emplace_back(enter, exit);
        }
    } else if (mode == 2) {
        ll left = rnd.next(0LL, 40LL);
        ll right = left + rnd.next(30LL, 100LL);
        for (int i = 0; i < n; ++i) {
            ll enter = rnd.next(left, right - 1);
            ll exit = rnd.next(enter + 1, right);
            intervals.emplace_back(enter, exit);
        }
    } else if (mode == 3) {
        ll commonL = rnd.next(0LL, 100LL);
        ll commonR = commonL + rnd.next(1LL, 100LL);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                intervals.emplace_back(commonL, commonR);
            } else if (rnd.next(0, 1) == 0) {
                intervals.emplace_back(commonL, commonL + rnd.next(1LL, 100LL));
            } else {
                intervals.emplace_back(rnd.next(0LL, commonR - 1), commonR);
            }
        }
    } else if (mode == 4) {
        ll cursor = rnd.next(0LL, 25LL);
        for (int i = 0; i < n; ++i) {
            ll len = rnd.next(1LL, 12LL);
            intervals.emplace_back(cursor, cursor + len);
            cursor += rnd.next(0LL, 8LL);
        }
    } else {
        ll base = MAX_T - rnd.next(1LL, 200LL);
        for (int i = 0; i < n; ++i) {
            ll enter = rnd.next(max(0LL, base - 100), MAX_T - 1);
            ll exit = rnd.next(enter + 1, MAX_T);
            intervals.emplace_back(enter, exit);
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(static_cast<int>(intervals.size()));
    for (const auto& interval : intervals) {
        println(interval.first, interval.second);
    }

    return 0;
}
