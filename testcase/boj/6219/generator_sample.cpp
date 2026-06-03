#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampInt(int value, int lo, int hi) {
    return min(max(value, lo), hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 4000000;
    const int maxWidth = 2000000;

    int mode = rnd.next(0, 5);
    int a;
    int b;
    int d;

    if (mode == 0) {
        a = rnd.next(1, 40);
        b = rnd.next(a, min(maxValue, a + rnd.next(0, 80)));
        d = rnd.next(0, 9);
    } else if (mode == 1) {
        vector<int> anchors = {101, 997, 1009, 1999, 9091, 99991, 100003, 1000003, 3999901};
        int center = rnd.any(anchors);
        int radius = rnd.next(0, 2500);
        a = clampInt(center - radius, 1, maxValue);
        b = clampInt(center + rnd.next(0, radius + 2500), a, maxValue);
        d = rnd.next(0, 9);
    } else if (mode == 2) {
        int width = rnd.next(0, 5000);
        a = rnd.next(1, maxValue - width);
        b = a + width;
        d = rnd.any(vector<int>{0, 1, 3, 7, 9});
    } else if (mode == 3) {
        int width = rnd.next(500000, maxWidth);
        a = rnd.next(1, maxValue - width);
        b = a + width;
        d = rnd.next(0, 9);
    } else if (mode == 4) {
        b = maxValue - rnd.next(0, 10000);
        int width = rnd.next(0, min(maxWidth, b - 1));
        a = b - width;
        d = rnd.any(vector<int>{0, 4, 9});
    } else {
        d = rnd.next(0, 9);
        int repeated = d;
        for (int i = 0; i < rnd.next(2, 6); ++i) {
            repeated = repeated * 10 + d;
        }
        int center = clampInt(repeated, 1, maxValue);
        int left = rnd.next(0, 1000);
        int right = rnd.next(0, 1000);
        a = clampInt(center - left, 1, maxValue);
        b = clampInt(center + right, a, maxValue);
    }

    if (b > a + maxWidth) {
        b = a + maxWidth;
    }

    println(a, b, d);
    return 0;
}
