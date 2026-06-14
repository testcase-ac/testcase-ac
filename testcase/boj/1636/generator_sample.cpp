#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> clampInterval(int s, int e) {
    s = max(1, min(200, s));
    e = max(1, min(200, e));
    if (s > e) swap(s, e);
    return {s, e};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (mode == 4) n = rnd.next(8, 45);

    vector<pair<int, int>> intervals;
    intervals.reserve(n);

    if (mode == 0) {
        int center = rnd.next(20, 180);
        for (int i = 0; i < n; ++i) {
            int radius = rnd.next(0, 20);
            int shift = rnd.next(-15, 15);
            intervals.push_back(clampInterval(center + shift - radius, center + shift + radius));
        }
    } else if (mode == 1) {
        int low = rnd.next(1, 70);
        int high = rnd.next(130, 200);
        for (int i = 0; i < n; ++i) {
            int base = (i % 2 == 0) ? low : high;
            int width = rnd.next(0, 12);
            int shift = rnd.next(-5, 5);
            intervals.push_back(clampInterval(base + shift, base + shift + width));
        }
    } else if (mode == 2) {
        int left = rnd.next(1, 40);
        int right = rnd.next(160, 200);
        for (int i = 0; i < n; ++i) {
            left = min(left + rnd.next(0, 4), 190);
            right = max(right - rnd.next(0, 4), left);
            intervals.push_back({left, right});
        }
    } else if (mode == 3) {
        int value = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            value = max(1, min(200, value + rnd.next(-35, 35)));
            if (rnd.next(0, 3) == 0) {
                int radius = rnd.next(1, 8);
                intervals.push_back(clampInterval(value - radius, value + radius));
            } else {
                intervals.push_back({value, value});
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int block = i % 4;
            if (block == 0) {
                intervals.push_back({1, rnd.next(1, 25)});
            } else if (block == 1) {
                intervals.push_back({rnd.next(176, 200), 200});
            } else if (block == 2) {
                int s = rnd.next(70, 110);
                intervals.push_back({s, rnd.next(s, min(200, s + 30))});
            } else {
                intervals.push_back({1, 200});
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, 200);
            int e = rnd.next(s, min(200, s + rnd.next(0, 60)));
            intervals.push_back({s, e});
        }
    }

    println(n);
    for (const auto& interval : intervals) {
        println(interval.first, interval.second);
    }

    return 0;
}
