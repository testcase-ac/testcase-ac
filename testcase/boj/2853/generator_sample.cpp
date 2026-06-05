#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    int todayDiff;
    vector<int> periods;

    if (mode == 0) {
        todayDiff = rnd.next(1, 30);
        periods.push_back(todayDiff);
        int count = rnd.next(1, min(5, todayDiff));
        for (int i = 0; i < count; ++i) {
            periods.push_back(rnd.next(1, todayDiff));
        }
    } else if (mode == 1) {
        int base = rnd.next(2, 12);
        int mult = rnd.next(2, 18);
        todayDiff = base * mult;
        periods.push_back(todayDiff);
        periods.push_back(base);
        if (base * 2 <= todayDiff) periods.push_back(base * 2);
        if (base * 3 <= todayDiff) periods.push_back(base * 3);
    } else if (mode == 2) {
        todayDiff = rnd.next(20, 120);
        periods.push_back(todayDiff);
        int count = rnd.next(2, 7);
        for (int i = 0; i < count; ++i) {
            periods.push_back(rnd.next(2, min(40, todayDiff)));
        }
    } else if (mode == 3) {
        todayDiff = rnd.next(200, 900);
        periods.push_back(todayDiff);
        int start = rnd.next(2, 15);
        for (int add = 0; add < rnd.next(2, 6); ++add) {
            periods.push_back(start + add * rnd.next(1, 4));
        }
    } else if (mode == 4) {
        todayDiff = rnd.next(100000000, 999999998);
        periods.push_back(todayDiff);
        int count = rnd.next(1, 4);
        for (int i = 0; i < count; ++i) {
            periods.push_back(rnd.next(10000000, 200000000));
        }
    } else {
        int step = rnd.next(1, 5);
        int count = rnd.next(2, 12);
        todayDiff = step * count;
        periods.push_back(todayDiff);
        periods.push_back(step);
    }

    set<int> diffs;
    diffs.insert(0);
    for (int period : periods) {
        if (period <= 0 || period > todayDiff) continue;
        for (int day = period; day <= todayDiff && static_cast<int>(diffs.size()) < 5000; day += period) {
            diffs.insert(day);
        }
    }
    diffs.insert(todayDiff);

    vector<int> days;
    days.reserve(diffs.size());
    for (int diff : diffs) {
        days.push_back(diff + 1);
    }

    println(static_cast<int>(days.size()));
    for (int day : days) {
        println(day);
    }

    return 0;
}
