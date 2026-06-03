#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, 365);
            int e = rnd.next(s, min(365, s + rnd.next(0, 8)));
            intervals.push_back({s, e});
        }
    } else if (mode == 1) {
        int clusters = rnd.next(1, 4);
        for (int c = 0; c < clusters; ++c) {
            int left = rnd.next(1, 340);
            int width = rnd.next(2, 18);
            int count = rnd.next(2, 10);
            int right = min(365, left + width);
            for (int i = 0; i < count; ++i) {
                int s = rnd.next(left, right);
                int e = rnd.next(s, right);
                intervals.push_back({s, e});
            }
        }
    } else if (mode == 2) {
        int count = rnd.next(5, 30);
        int base = rnd.next(1, 345);
        int right = min(365, base + rnd.next(8, 20));
        for (int i = 0; i < count; ++i) {
            int s = rnd.next(base, min(right, base + 5));
            int e = rnd.next(max(s, right - 5), right);
            intervals.push_back({s, e});
        }
    } else if (mode == 3) {
        int day = 1;
        while (day <= 365 && (int)intervals.size() < 25) {
            int gap = rnd.next(0, 4);
            day += gap;
            if (day > 365) break;

            int span = rnd.next(1, 10);
            int count = rnd.next(1, 5);
            int right = min(365, day + span - 1);
            for (int i = 0; i < count; ++i) {
                int s = rnd.next(day, right);
                int e = rnd.next(s, right);
                intervals.push_back({s, e});
            }
            day = right + rnd.next(1, 5);
        }
    } else if (mode == 4) {
        intervals.push_back({1, rnd.next(1, 365)});
        intervals.push_back({rnd.next(1, 365), 365});
        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; ++i) {
            int s = rnd.next(1, 365);
            int e = rnd.next(s, 365);
            intervals.push_back({s, e});
        }
    } else {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, 365);
            int maxLen = rnd.any(vector<int>{0, 1, 3, 10, 30, 120});
            int e = rnd.next(s, min(365, s + maxLen));
            intervals.push_back({s, e});
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println((int)intervals.size());
    for (auto [s, e] : intervals) {
        println(s, e);
    }

    return 0;
}
