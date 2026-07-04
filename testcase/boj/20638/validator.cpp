#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long l = inf.readLong(1LL, 1000000000000LL, "L");
    inf.readEoln();

    vector<pair<long long, long long>> intervals;
    intervals.reserve(n);

    for (int i = 0; i < n; ++i) {
        long long left = inf.readLong(0LL, l - 1, "l_i");
        inf.readSpace();
        long long right = inf.readLong(left + 1, l, "r_i");
        inf.readEoln();
        intervals.push_back({left, right});
    }

    sort(intervals.begin(), intervals.end());

    long long covered_until = 0;
    for (int i = 0; i < n; ++i) {
        ensuref(intervals[i].first <= covered_until,
                "union of intervals has a gap before %lld", intervals[i].first);
        covered_until = max(covered_until, intervals[i].second);
        if (covered_until == l) {
            break;
        }
    }

    ensuref(covered_until == l, "union of all intervals does not cover [0, L)");

    inf.readEof();
}
