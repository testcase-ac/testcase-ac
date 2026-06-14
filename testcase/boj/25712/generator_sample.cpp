#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<int, int>;

vector<Interval> makeRandomColumn(int n, int count) {
    vector<int> cuts;
    for (int i = 0; i < count * 2; ++i) {
        cuts.push_back(rnd.next(1, n));
    }
    sort(cuts.begin(), cuts.end());

    vector<Interval> intervals;
    int previousBottom = 0;
    for (int i = 0; i + 1 < static_cast<int>(cuts.size()) &&
                    static_cast<int>(intervals.size()) < count;
         i += 2) {
        int top = max(cuts[i], previousBottom + 1);
        if (top > n) {
            break;
        }
        int bottom = rnd.next(top, max(top, cuts[i + 1]));
        intervals.emplace_back(top, bottom);
        previousBottom = bottom;
    }

    if (intervals.empty()) {
        int row = rnd.next(1, n);
        intervals.emplace_back(row, row);
    }
    return intervals;
}

vector<Interval> makeColumnAround(int n, int focus, bool includeFocus) {
    vector<Interval> intervals;
    if (includeFocus) {
        int top = rnd.next(max(1, focus - 2), focus);
        int bottom = rnd.next(focus, min(n, focus + 2));
        intervals.emplace_back(top, bottom);
    }

    int extra = rnd.next(0, 3);
    for (int tries = 0; tries < 40 && extra > 0; ++tries) {
        int len = rnd.next(1, min(5, n));
        int top = rnd.next(1, n - len + 1);
        int bottom = top + len - 1;
        bool ok = true;
        for (auto [a, b] : intervals) {
            if (max(a, top) <= min(b, bottom)) {
                ok = false;
            }
        }
        if (!ok) {
            continue;
        }
        intervals.emplace_back(top, bottom);
        --extra;
    }

    sort(intervals.begin(), intervals.end());
    vector<Interval> merged;
    for (auto [top, bottom] : intervals) {
        if (!merged.empty() && top <= merged.back().second) {
            merged.back().second = max(merged.back().second, bottom);
        } else {
            merged.emplace_back(top, bottom);
        }
    }
    while (static_cast<int>(merged.size()) > 10) {
        merged.pop_back();
    }
    return merged;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 40);
    if (mode == 5) {
        n = rnd.next(100000000 - 100, 1000000000);
    }
    int m = rnd.next(1, 12);
    int focus = rnd.next(1, n);

    vector<vector<Interval>> columns(m);
    if (mode <= 1) {
        for (int col = 0; col < m; ++col) {
            focus = rnd.next(max(1, focus - 1), min(n, focus + 1));
            columns[col] = makeColumnAround(n, focus, true);
        }
    } else if (mode <= 3) {
        int breakCol = rnd.next(0, m - 1);
        for (int col = 0; col < m; ++col) {
            bool includeFocus = col != breakCol;
            columns[col] = makeColumnAround(n, focus, includeFocus);
            if (columns[col].empty()) {
                columns[col] = makeRandomColumn(n, 1);
            }
        }
    } else {
        for (int col = 0; col < m; ++col) {
            columns[col] = makeRandomColumn(n, rnd.next(1, min(10, n)));
        }
    }

    println(n, m);
    vector<int> lengths;
    for (const auto& column : columns) {
        lengths.push_back(static_cast<int>(column.size()) * 2);
    }
    println(lengths);

    for (const auto& column : columns) {
        vector<int> encoded;
        for (auto [top, bottom] : column) {
            encoded.push_back(top);
            encoded.push_back(bottom);
        }
        println(encoded);
    }

    return 0;
}
