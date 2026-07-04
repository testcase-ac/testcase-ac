#include "testlib.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 1000, "N");
        inf.readEoln();

        long long hikers = 0;
        map<int, vector<pair<long long, long long>>> speedIntervalsByDegree;

        for (int i = 1; i <= N; ++i) {
            int D = inf.readInt(1, 359, "D_i");
            inf.readSpace();
            int H = inf.readInt(1, 500000, "H_i");
            inf.readSpace();
            long long M = inf.readLong(1LL, 1000000000LL, "M_i");
            inf.readEoln();

            hikers += H;
            ensuref(hikers <= 500000,
                    "total hikers exceeds 500000 in test case %d", tc);

            speedIntervalsByDegree[D].push_back({M, M + H - 1});
        }

        for (auto& entry : speedIntervalsByDegree) {
            auto& intervals = entry.second;
            sort(intervals.begin(), intervals.end());
            for (int i = 1; i < (int)intervals.size(); ++i) {
                ensuref(intervals[i - 1].second < intervals[i].first,
                        "duplicate hiker speed at starting degree %d", entry.first);
            }
        }
    }

    inf.readEof();
}
