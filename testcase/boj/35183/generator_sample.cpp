#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> clampInterval(int l, int r) {
    l = max(l, 1);
    r = min(r, 1000);
    if (l > r) {
        l = r = max(1, min(1000, (l + r) / 2));
    }
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 120 : 35);
    vector<pair<int, int>> intervals;
    intervals.reserve(n);

    if (mode == 0) {
        int pos = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            pos += rnd.next(-1, 1);
            pos = max(1, min(1000, pos));
            int slack = rnd.next(0, 5);
            intervals.push_back(clampInterval(pos - slack, pos + slack));
        }
    } else if (mode == 1) {
        int pos = rnd.next(10, 990);
        int missAt = n == 1 ? 0 : rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i == missAt) {
                int far = pos <= 500 ? rnd.next(800, 1000) : rnd.next(1, 200);
                int width = rnd.next(0, 8);
                intervals.push_back(clampInterval(far - width, far + width));
            } else {
                pos += rnd.next(-1, 1);
                pos = max(1, min(1000, pos));
                int width = rnd.next(0, 3);
                intervals.push_back(clampInterval(pos - width, pos + width));
            }
        }
    } else if (mode == 2) {
        int left = rnd.next(1, 80);
        int right = rnd.next(920, 1000);
        for (int i = 0; i < n; ++i) {
            int center = (i % 2 == 0) ? left : right;
            int width = rnd.next(0, 10);
            intervals.push_back(clampInterval(center - width, center + width));
        }
    } else if (mode == 3) {
        int anchor = rnd.next(1, 2) == 1 ? rnd.next(1, 20) : rnd.next(981, 1000);
        for (int i = 0; i < n; ++i) {
            anchor += rnd.next(-1, 1);
            anchor = max(1, min(1000, anchor));
            int width = rnd.next(0, 12);
            intervals.push_back(clampInterval(anchor - width, anchor + width));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int l = rnd.next(1, 1000);
            int r = rnd.next(l, min(1000, l + rnd.next(0, 50)));
            intervals.push_back({l, r});
        }
    } else {
        int center = rnd.next(100, 900);
        int drift = rnd.next(-1, 1);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) == 0) {
                center = rnd.next(1, 1000);
                drift = rnd.next(-1, 1);
            } else {
                center += drift + rnd.next(-1, 1);
            }
            center = max(1, min(1000, center));
            int width = rnd.wnext(40, -2);
            intervals.push_back(clampInterval(center - width, center + width));
        }
    }

    println((int)intervals.size());
    for (auto [l, r] : intervals) {
        println(l, r);
    }

    return 0;
}
