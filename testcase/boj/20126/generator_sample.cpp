#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<long long, long long>;

static vector<Interval> makeIntervalsFromGaps(long long s, const vector<long long>& gaps,
                                              const vector<long long>& lengths) {
    vector<Interval> intervals;
    long long cur = gaps[0];
    for (int i = 0; i < (int)lengths.size(); ++i) {
        intervals.push_back({cur, cur + lengths[i]});
        cur += lengths[i] + gaps[i + 1];
    }
    ensure(cur <= s);
    return intervals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 10);
    long long m = rnd.next(1LL, 20LL);
    long long s = rnd.next(m, 80LL);
    vector<Interval> intervals;

    if (mode == 0) {
        m = rnd.next(1LL, 10LL);
        long long firstGap = rnd.next(m, m + 10);
        n = rnd.next(1, 8);
        vector<long long> gaps(n + 1, 0), lengths(n);
        gaps[0] = firstGap;
        for (int i = 0; i < n; ++i) {
            lengths[i] = rnd.next(1LL, 5LL);
            if (i + 1 < n) gaps[i + 1] = rnd.next(0LL, 3LL);
        }
        gaps[n] = rnd.next(0LL, 5LL);
        s = firstGap;
        for (long long x : lengths) s += x;
        for (int i = 1; i <= n; ++i) s += gaps[i];
        intervals = makeIntervalsFromGaps(s, gaps, lengths);
    } else if (mode == 1) {
        m = rnd.next(2LL, 12LL);
        n = rnd.next(2, 9);
        vector<long long> gaps(n + 1, 0), lengths(n);
        int openGap = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) lengths[i] = rnd.next(1LL, 6LL);
        for (int i = 1; i < n; ++i) gaps[i] = rnd.next(0LL, m - 1);
        gaps[openGap] = rnd.next(m, m + 8);
        gaps[n] = rnd.next(0LL, m - 1);
        s = 0;
        for (long long x : lengths) s += x;
        for (long long x : gaps) s += x;
        intervals = makeIntervalsFromGaps(s, gaps, lengths);
    } else if (mode == 2) {
        m = rnd.next(1LL, 12LL);
        n = rnd.next(1, 8);
        vector<long long> gaps(n + 1, 0), lengths(n);
        for (int i = 0; i < n; ++i) {
            lengths[i] = rnd.next(1LL, 6LL);
            if (i + 1 < n) gaps[i + 1] = rnd.next(0LL, m - 1);
        }
        gaps[n] = rnd.next(m, m + 12);
        s = 0;
        for (long long x : lengths) s += x;
        for (long long x : gaps) s += x;
        intervals = makeIntervalsFromGaps(s, gaps, lengths);
    } else if (mode == 3) {
        m = rnd.next(2LL, 14LL);
        n = rnd.next(1, 10);
        vector<long long> gaps(n + 1, 0), lengths(n);
        for (int i = 0; i < n; ++i) {
            lengths[i] = rnd.next(1LL, 8LL);
            gaps[i] = rnd.next(0LL, m - 1);
        }
        gaps[n] = rnd.next(0LL, m - 1);
        s = 0;
        for (long long x : lengths) s += x;
        for (long long x : gaps) s += x;
        intervals = makeIntervalsFromGaps(s, gaps, lengths);
    } else if (mode == 4) {
        m = rnd.next(1LL, 10LL);
        n = rnd.next(2, 10);
        long long cur = rnd.next(0LL, m - 1);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1LL, 7LL);
            intervals.push_back({cur, cur + len});
            cur += len;
            if (i + 1 < n && rnd.next(0, 2) == 0) cur += rnd.next(0LL, m - 1);
        }
        s = cur + rnd.next(0LL, m + 5);
    } else if (mode == 5) {
        m = rnd.next(1LL, 1000000000LL);
        s = 1000000000LL;
        n = rnd.next(1, 6);
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            long long remaining = s - cur - (n - i - 1);
            long long len = rnd.next(1LL, max(1LL, min(1000000LL, remaining)));
            intervals.push_back({cur, cur + len});
            cur += len;
            if (i + 1 < n) cur += rnd.next(0LL, 1000000LL);
        }
    } else {
        n = 1;
        m = rnd.next(1LL, 20LL);
        s = rnd.next(m, 60LL);
        long long x = rnd.next(0LL, s - 1);
        long long y = rnd.next(1LL, s - x);
        intervals.push_back({x, x + y});
    }

    shuffle(intervals.begin(), intervals.end());

    println((int)intervals.size(), m, s);
    for (auto [l, r] : intervals) {
        println(l, r - l);
    }

    return 0;
}
