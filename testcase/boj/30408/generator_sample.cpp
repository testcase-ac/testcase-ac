#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_N = 1000000000000000000LL;

struct Interval {
    ll l;
    ll r;
};

vector<Interval> buildIntervals(ll m) {
    vector<Interval> intervals;
    ll l = m;
    ll r = m;
    while (l <= MAX_N) {
        intervals.push_back({l, min(r, MAX_N)});
        if (l > (MAX_N + 1) / 2) break;
        l = 2 * l - 1;
        r = min(MAX_N, 2 * r + 1);
    }
    return intervals;
}

ll randomLarge() {
    return MAX_N - rnd.next(0LL, 1000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    ll n = 1;
    ll m = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 100LL);
        m = rnd.next(1LL, n);
    } else if (mode == 1) {
        m = rnd.next(1LL, 1000000LL);
        auto intervals = buildIntervals(m);
        Interval chosen = rnd.any(intervals);
        n = rnd.next(chosen.l, chosen.r);
    } else if (mode == 2) {
        m = rnd.next(3LL, 1000000LL);
        auto intervals = buildIntervals(m);
        vector<Interval> gaps;
        for (size_t i = 0; i + 1 < intervals.size(); ++i) {
            ll gl = intervals[i].r + 1;
            ll gr = intervals[i + 1].l - 1;
            if (gl <= gr) gaps.push_back({gl, gr});
        }
        Interval gap = rnd.any(gaps);
        n = rnd.next(gap.l, gap.r);
    } else if (mode == 3) {
        n = randomLarge();
        m = rnd.next(1LL, n);
    } else if (mode == 4) {
        m = rnd.next(1LL, 1000000000000LL);
        auto intervals = buildIntervals(m);
        Interval chosen = rnd.any(intervals);
        n = rnd.next(max(chosen.l, chosen.r - 1000), chosen.r);
    } else {
        n = rnd.next(1LL, MAX_N);
        m = n;
    }

    println(n, m);
    return 0;
}
