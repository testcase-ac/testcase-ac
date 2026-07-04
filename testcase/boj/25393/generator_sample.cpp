#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Interval = pair<int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxCoord = 1000000;
    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 14);
    int q = rnd.next(8, 18);

    vector<Interval> intervals;
    vector<Interval> queries;

    auto addInterval = [&](int l, int r) {
        intervals.push_back({l, r});
    };

    auto addQuery = [&](int l, int r) {
        queries.push_back({l, r});
    };

    if (mode == 0) {
        int base = rnd.next(0, 30);
        addInterval(base, base + 20);
        addInterval(base + 5, base + 15);
        addInterval(base + 10, base + 25);
        addQuery(base + 5, base + 15);
        addQuery(base + 10, base + 15);
        addQuery(base + 4, base + 16);
    } else if (mode == 1) {
        int left = rnd.next(0, 20);
        int right = rnd.next(40, 80);
        for (int i = 0; i < 4; ++i) {
            addInterval(left + rnd.next(0, 5), right - rnd.next(0, 5));
        }
        addQuery(left, right);
        addQuery(left + 2, right - 2);
    } else if (mode == 2) {
        addInterval(0, maxCoord);
        addInterval(0, rnd.next(1, 20));
        addInterval(maxCoord - rnd.next(1, 20), maxCoord);
        addQuery(0, maxCoord);
        addQuery(0, 1);
        addQuery(maxCoord - 1, maxCoord);
    } else if (mode == 3) {
        int center = rnd.next(100, 200);
        for (int i = 0; i < 5; ++i) {
            addInterval(center - rnd.next(1, 20), center + rnd.next(1, 20));
        }
        addQuery(center - 1, center + 1);
        addQuery(center, center + 1);
    } else {
        int start = rnd.next(0, 50);
        for (int i = 0; i < 5; ++i) {
            int l = start + i * rnd.next(1, 4);
            addInterval(l, l + rnd.next(1, 8));
        }
        addQuery(start, start + 1);
        addQuery(start + 3, start + 7);
    }

    while ((int)intervals.size() < n) {
        int l = rnd.next(0, maxCoord - 1);
        int span = rnd.next(1, min(80, maxCoord - l));
        addInterval(l, l + span);
    }

    for (const auto& interval : intervals) {
        if ((int)queries.size() >= q) break;
        if (rnd.next(0, 2) == 0) {
            addQuery(interval.first, interval.second);
        }
    }

    while ((int)queries.size() < q) {
        int kind = rnd.next(0, 2);
        if (kind == 0) {
            const auto& a = rnd.any(intervals);
            const auto& b = rnd.any(intervals);
            int l = max(a.first, b.first);
            int r = min(a.second, b.second);
            if (l < r) {
                addQuery(l, r);
                continue;
            }
        } else if (kind == 1) {
            int l = rnd.next(0, maxCoord - 1);
            addQuery(l, l + rnd.next(1, min(100, maxCoord - l)));
            continue;
        } else {
            int l = rnd.next(0, 50);
            addQuery(l, l + rnd.next(1, 50));
            continue;
        }
    }

    shuffle(intervals.begin(), intervals.end());
    shuffle(queries.begin(), queries.end());

    println((int)intervals.size());
    for (const auto& interval : intervals) {
        println(interval.first, interval.second);
    }
    println((int)queries.size());
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
