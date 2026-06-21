#include "testlib.h"
#include <algorithm>
#include <array>

using namespace std;

struct RectSpec {
    int nearX;
    int nearY;
    int farX;
    int farY;
};

static pair<int, int> chooseSpan(int mode) {
    if (mode == 0) {
        int lo = rnd.next(1, 8);
        int len = rnd.next(1, 8);
        return {lo, lo + len};
    }
    if (mode == 1) {
        int lo = rnd.next(1, 20);
        int len = rnd.wnext(35, -2) + 1;
        return {lo, lo + len};
    }
    if (mode == 2) {
        int len = rnd.next(1, 20);
        int hi = 100000 - rnd.next(0, 30);
        return {hi - len, hi};
    }

    int lo = rnd.next(1, 200);
    int hi = rnd.next(lo + 1, min(100000, lo + rnd.next(1, 250)));
    return {lo, hi};
}

static RectSpec makeRect(int quadrant, int mode) {
    auto xs = chooseSpan(mode);
    auto ys = chooseSpan((mode + rnd.next(0, 2)) % 4);

    RectSpec rect{};
    if (quadrant == 1) {
        rect = {xs.first, ys.first, xs.second, ys.second};
    } else if (quadrant == 2) {
        rect = {-xs.first, ys.first, -xs.second, ys.second};
    } else if (quadrant == 3) {
        rect = {-xs.first, -ys.first, -xs.second, -ys.second};
    } else {
        rect = {xs.first, -ys.first, xs.second, -ys.second};
    }
    return rect;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    array<RectSpec, 4> rects{};
    for (int quadrant = 1; quadrant <= 4; ++quadrant) {
        int localMode = mode;
        if (rnd.next(0, 99) < 35) {
            localMode = rnd.next(0, 3);
        }
        rects[quadrant - 1] = makeRect(quadrant, localMode);
    }

    for (const RectSpec& rect : rects) {
        println(rect.nearX, rect.nearY, rect.farX, rect.farY);
    }

    return 0;
}
