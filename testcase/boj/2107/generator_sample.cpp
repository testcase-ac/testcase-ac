#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<int, int>;

vector<int> coordinateMap(int count) {
    vector<int> xs(count + 1);
    int current = 0;
    for (int i = 1; i <= count; ++i) {
        current += rnd.next(1, 7);
        xs[i] = current;
    }

    int offset = 0;
    if (rnd.next(4) == 0) {
        offset = 2000000000 - xs[count];
    } else {
        offset = rnd.next(0, 1000);
    }
    for (int i = 1; i <= count; ++i) {
        xs[i] += offset;
    }
    return xs;
}

void addInterval(vector<Interval>& intervals, int a, int b) {
    if (a > b) swap(a, b);
    intervals.emplace_back(a, b);
}

vector<Interval> buildByRanks(int n, int mode) {
    vector<Interval> intervals;

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            addInterval(intervals, i, 2 * n + 1 - i);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            addInterval(intervals, 2 * i + 1, 2 * i + 2);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            addInterval(intervals, i, i + n);
        }
    } else if (mode == 3 && n >= 2) {
        addInterval(intervals, 1, 2 * n);
        int remaining = n - 1;
        int left = 2;
        while (remaining > 0) {
            if (remaining >= 2 && rnd.next(2) == 0) {
                addInterval(intervals, left, left + 3);
                addInterval(intervals, left + 1, left + 2);
                left += 4;
                remaining -= 2;
            } else {
                addInterval(intervals, left, left + 1);
                left += 2;
                --remaining;
            }
        }
    } else {
        vector<int> ranks(2 * n);
        for (int i = 0; i < 2 * n; ++i) {
            ranks[i] = i + 1;
        }
        shuffle(ranks.begin(), ranks.end());
        for (int i = 0; i < n; ++i) {
            addInterval(intervals, ranks[2 * i], ranks[2 * i + 1]);
        }
    }

    return intervals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 10);
    } else if (sizeMode == 3) {
        n = rnd.next(11, 40);
    } else {
        n = rnd.next(41, 120);
    }

    int mode = rnd.next(5);
    vector<Interval> intervals = buildByRanks(n, mode);
    vector<int> xs = coordinateMap(2 * n);

    shuffle(intervals.begin(), intervals.end());

    println(n);
    for (auto [a, b] : intervals) {
        println(xs[a], xs[b]);
    }

    return 0;
}
