#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = mode == 0 ? rnd.next(1, 8) : rnd.next(2, 24);
    int tallestIndex = rnd.next(1, n);

    vector<pair<int, int>> allIntervals;
    for (int left = 1; left <= n; ++left) {
        for (int right = left + 1; right <= n; ++right) {
            allIntervals.push_back({left, right});
        }
    }
    shuffle(allIntervals.begin(), allIntervals.end());

    vector<pair<int, int>> lines;
    set<pair<int, int>> uniqueIntervals;
    vector<int> cover(n + 2, 0);

    auto canAddUnique = [&](int left, int right, int coverLimit) {
        if (uniqueIntervals.count({left, right}) != 0) {
            return true;
        }
        for (int cow = left + 1; cow < right; ++cow) {
            if (cover[cow] + 1 > coverLimit) {
                return false;
            }
        }
        return true;
    };

    auto addLine = [&](int left, int right, int coverLimit) {
        if (left > right) {
            swap(left, right);
        }
        if (!canAddUnique(left, right, coverLimit)) {
            return false;
        }
        if (uniqueIntervals.insert({left, right}).second) {
            for (int cow = left + 1; cow < right; ++cow) {
                ++cover[cow];
            }
        }
        if (rnd.next(0, 1) == 1) {
            swap(left, right);
        }
        lines.push_back({left, right});
        return true;
    };

    int coverLimit = mode == 1 ? rnd.next(1, 3) : rnd.next(1, 6);
    if (mode == 1) {
        coverLimit = 1;
    }

    if (mode == 0 || n == 1) {
        // Keep R at zero for boundary cases, including N = 1.
    } else if (mode == 1) {
        int left = rnd.next(1, n - 1);
        int right = rnd.next(left + 1, n);
        int repeatCount = rnd.next(2, min(8, 10000));
        for (int i = 0; i < repeatCount; ++i) {
            addLine(left, right, coverLimit);
        }
    } else if (mode == 2) {
        for (int width = n - 1; width >= 1 && static_cast<int>(lines.size()) < 20; --width) {
            int left = rnd.next(1, n - width);
            int right = left + width;
            addLine(left, right, coverLimit);
        }
    } else {
        int target = rnd.next(1, min<int>(30, allIntervals.size()));
        for (auto [left, right] : allIntervals) {
            if (static_cast<int>(lines.size()) >= target) {
                break;
            }
            addLine(left, right, coverLimit);
            if (!lines.empty() && rnd.next(0, 5) == 0) {
                auto duplicate = rnd.any(lines);
                addLine(duplicate.first, duplicate.second, coverLimit);
            }
        }
    }

    int maxCover = 0;
    for (int cow = 1; cow <= n; ++cow) {
        maxCover = max(maxCover, cover[cow]);
    }
    int h = rnd.next(maxCover + 1, maxCover + 20);

    println(n, tallestIndex, h, static_cast<int>(lines.size()));
    for (auto [a, b] : lines) {
        println(a, b);
    }

    return 0;
}
