#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(0, 1000000, "M");
    inf.readSpace();
    long long k = inf.readLong(n, 1000000000000LL, "K");
    inf.readEoln();

    vector<pair<long long, long long>> intervals;
    intervals.reserve(m);
    long long forbidden = 0;

    for (int i = 0; i < m; ++i) {
        long long l = inf.readLong(0LL, k - 1, "l_i");
        inf.readSpace();
        long long r = inf.readLong(l, k - 1, "r_i");
        inf.readEoln();

        intervals.emplace_back(l, r);
        forbidden += r - l + 1;
    }

    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < m; ++i) {
        ensuref(intervals[i - 1].second < intervals[i].first,
                "forbidden intervals overlap: [%lld, %lld] and [%lld, %lld]",
                intervals[i - 1].first, intervals[i - 1].second,
                intervals[i].first, intervals[i].second);
    }

    ensuref(k - forbidden >= n,
            "not enough allowed queue positions: allowed=%lld, N=%lld",
            k - forbidden, n);

    inf.readEof();
}
