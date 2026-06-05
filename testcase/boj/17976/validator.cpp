#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<pair<long long, long long>> intervals;
    intervals.reserve(n);
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(0LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long l = inf.readLong(1LL, 1000000000LL, "l_i");
        inf.readEoln();

        intervals.push_back({x, x + l});
    }
    inf.readEof();

    sort(intervals.begin(), intervals.end());
    long long maxRight = intervals[0].second;
    int maxRightIndex = 0;
    for (int i = 1; i < n; ++i) {
        ensuref(maxRight < intervals[i].second,
                "thread %d [%lld, %lld] is totally contained by thread %d ending at %lld",
                i + 1, intervals[i].first, intervals[i].second, maxRightIndex + 1, maxRight);
        if (intervals[i].second > maxRight) {
            maxRight = intervals[i].second;
            maxRightIndex = i;
        }
    }
}
