#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = 1;
    int n = 1;
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        k = rnd.next(1, 8);
        n = rnd.next(1, 12);
        int day = rnd.next(1, k);
        for (int i = 0; i < n; ++i) intervals.push_back({day, day});
    } else if (mode == 1) {
        k = rnd.next(2, 30);
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, min(3, k));
            int e = rnd.next(max(s, k - 2), k);
            intervals.push_back({s, e});
        }
    } else if (mode == 2) {
        k = rnd.next(2, 40);
        n = rnd.next(2, 24);
        for (int i = 0; i < n; ++i) {
            int s = rnd.any(vector<int>{1, rnd.next(1, k), k});
            int e = rnd.any(vector<int>{s, rnd.next(s, k), k});
            intervals.push_back({s, e});
        }
    } else if (mode == 3) {
        k = rnd.next(5, 60);
        n = rnd.next(5, 30);
        int center = rnd.next(2, k - 1);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, center);
            int e = rnd.next(center, k);
            intervals.push_back({s, e});
        }
    } else if (mode == 4) {
        k = rnd.next(6, 60);
        n = rnd.next(4, 24);
        int left = rnd.next(1, k / 2);
        int right = rnd.next((k + 1) / 2, k);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(left, min(right, left + i % max(1, right - left + 1)));
            int e = rnd.next(max(s, right - i % max(1, right - left + 1)), right);
            intervals.push_back({s, e});
        }
    } else {
        k = rnd.next(8, 80);
        n = rnd.next(8, 35);
        int maxLen = rnd.next(1, min(12, k));
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(1, k);
            int e = min(k, s + rnd.next(0, maxLen - 1));
            intervals.push_back({s, e});
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(n, k);
    for (auto [s, e] : intervals) println(s, e);

    return 0;
}
