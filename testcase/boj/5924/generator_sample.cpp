#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int horizontalCount = rnd.next(1, 8);
    int verticalCount = rnd.next(1, 8);
    if (mode == 0) verticalCount = 0;
    if (mode == 1) horizontalCount = 0;
    if (mode == 4) {
        horizontalCount = rnd.next(7, 12);
        verticalCount = rnd.next(7, 12);
    }

    long long base = (mode == 3 ? 1000000000LL - 200 : rnd.next(1, 500));
    vector<long long> xs;
    vector<long long> ys;
    for (int i = 0; i < verticalCount; ++i) xs.push_back(base + 2 * i + 1);
    for (int i = 0; i < horizontalCount; ++i) ys.push_back(base + 2 * i + 2);

    vector<Segment> segments;
    for (int i = 0; i < horizontalCount; ++i) {
        long long y = ys[i];
        long long left = base;
        long long right = base + 2 * max(1, verticalCount) + 2;
        if (mode == 2 && verticalCount > 0) {
            int anchor = rnd.next(0, verticalCount - 1);
            left = xs[anchor];
            right = left + rnd.next(1, 5);
        } else if (mode != 4) {
            left += rnd.next(0, 1);
            right -= rnd.next(0, 1);
        }
        if (rnd.next(0, 1)) swap(left, right);
        segments.push_back({left, y, right, y});
    }

    for (int i = 0; i < verticalCount; ++i) {
        long long x = xs[i];
        long long bottom = base + 1;
        long long top = base + 2 * max(1, horizontalCount) + 3;
        if (mode == 2 && horizontalCount > 0) {
            int anchor = rnd.next(0, horizontalCount - 1);
            bottom = ys[anchor];
            top = bottom + rnd.next(1, 5);
        } else if (mode != 4) {
            bottom += rnd.next(0, 1);
            top -= rnd.next(0, 1);
        }
        if (rnd.next(0, 1)) swap(bottom, top);
        segments.push_back({x, bottom, x, top});
    }

    shuffle(segments.begin(), segments.end());
    println((int)segments.size());
    for (const Segment& segment : segments) {
        println(segment.x1, segment.y1, segment.x2, segment.y2);
    }

    return 0;
}
