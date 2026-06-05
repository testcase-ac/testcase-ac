#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Interval = pair<int, int>;

vector<Interval> buildIntervals(int targetCount, int maxTime, int maxLen, bool allowLate) {
    vector<Interval> intervals;
    int current = allowLate ? rnd.next(0, min(900, maxTime - 1)) : rnd.next(0, min(20, maxTime - 1));

    while ((int)intervals.size() < targetCount && current < maxTime) {
        int remaining = maxTime - current;
        int len = rnd.next(1, min(maxLen, remaining));
        intervals.push_back({current, current + len});
        current += len + rnd.next(1, 12);
    }

    if (intervals.empty()) {
        int start = rnd.next(0, maxTime - 1);
        intervals.push_back({start, start + 1});
    }

    return intervals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<vector<Interval>> participants;
    int t = 1;

    if (mode == 0) {
        t = rnd.next(1, 5);
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(0, 10);
            participants.push_back({{start, start + rnd.next(1, 5)}});
        }
    } else if (mode == 1) {
        t = rnd.any(vector<int>{500, 750, 1000});
        int n = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            int firstEnd = rnd.next(1, 500);
            vector<Interval> intervals = {{0, firstEnd}};
            if (firstEnd + 1 < 1000) intervals.push_back({firstEnd + 1, 1000});
            participants.push_back(intervals);
        }
    } else if (mode == 2) {
        t = rnd.next(2, 20);
        int n = rnd.next(3, 10);
        int commonStart = rnd.next(0, 40);
        int commonEnd = rnd.next(commonStart + t, min(1000, commonStart + t + 40));
        for (int i = 0; i < n; ++i) {
            vector<Interval> intervals;
            if (commonStart > 1 && rnd.next(0, 1)) intervals.push_back({0, commonStart - 1});
            intervals.push_back({commonStart, commonEnd});
            if (commonEnd + 1 < 1000 && rnd.next(0, 1)) {
                int end = rnd.next(commonEnd + 2, min(1000, commonEnd + 30));
                intervals.push_back({commonEnd + 1, end});
            }
            participants.push_back(intervals);
        }
    } else if (mode == 3) {
        t = rnd.next(1, 80);
        int n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) {
            int start = rnd.next(0, 120);
            int end = rnd.next(start + 1, min(1000, start + rnd.next(50, 250)));
            participants.push_back({{start, end}});
        }
    } else if (mode == 4) {
        t = rnd.next(1, 100);
        int n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(1, 6);
            participants.push_back(buildIntervals(k, 1000, rnd.next(1, 60), rnd.next(0, 1)));
        }
    } else {
        t = rnd.next(1, 1000);
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int k = rnd.next(1, 4);
            participants.push_back(buildIntervals(k, 1000, rnd.next(1, 20), true));
        }
    }

    println((int)participants.size(), t);
    for (const auto& intervals : participants) {
        println((int)intervals.size());
        for (const auto& interval : intervals) println(interval.first, interval.second);
    }

    return 0;
}
