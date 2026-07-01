#include "testlib.h"

#include <map>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1000, "n");
    inf.readEoln();

    vector<pair<long long, long long>> points;
    set<pair<long long, long long>> seen;
    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        pair<long long, long long> point = {x, y};
        ensuref(seen.insert(point).second,
                "duplicate point at index %d: (%lld, %lld)", i + 1, x, y);
        points.push_back(point);
    }

    map<pair<long long, long long>, long long> pairSums;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ++pairSums[{points[i].first + points[j].first,
                        points[i].second + points[j].second}];
        }
    }

    long long answer = 0;
    for (const auto& entry : pairSums) {
        long long count = entry.second;
        answer += count * (count - 1) / 2;
        ensuref(answer <= 2147483647LL,
                "answer does not fit signed 32-bit integer");
    }

    inf.readEof();
}
