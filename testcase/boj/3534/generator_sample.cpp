#include "testlib.h"

#include <algorithm>
#include <array>

using namespace std;

namespace {

constexpr long long kCoordLimit = 100000000LL;

struct Frame {
    long long ox1;
    long long oy1;
    long long ox2;
    long long oy2;
    long long ix1;
    long long iy1;
    long long ix2;
    long long iy2;
};

long long chooseOrigin(long long width, long long height, bool nearLimit) {
    long long span = max(width, height);
    if (nearLimit) {
        long long edge = kCoordLimit - span - 5;
        return rnd.next(0, 1) == 0 ? rnd.next(-kCoordLimit, -edge) : rnd.next(edge, kCoordLimit - span);
    }
    return rnd.next(-50LL, 50LL);
}

Frame makeFrame(long long width, long long height, int mode) {
    bool nearLimit = mode == 3;
    long long x1 = chooseOrigin(width, height, nearLimit);
    long long y1 = chooseOrigin(height, width, nearLimit);
    long long x2 = x1 + width;
    long long y2 = y1 + height;

    long long leftMargin = rnd.next(1LL, max(1LL, (width - 1) / 3));
    long long rightMargin = rnd.next(1LL, max(1LL, (width - 1) / 3));
    long long bottomMargin = rnd.next(1LL, max(1LL, (height - 1) / 3));
    long long topMargin = rnd.next(1LL, max(1LL, (height - 1) / 3));

    if (mode == 2) {
        leftMargin = 1;
        bottomMargin = 1;
        rightMargin = rnd.next(1LL, max(1LL, (width - 1) / 2));
        topMargin = rnd.next(1LL, max(1LL, (height - 1) / 2));
    }

    if (leftMargin + rightMargin >= width) {
        leftMargin = 1;
        rightMargin = width - 2;
    }
    if (bottomMargin + topMargin >= height) {
        bottomMargin = 1;
        topMargin = height - 2;
    }

    Frame frame{x1, y1, x2, y2, x1 + leftMargin, y1 + bottomMargin, x2 - rightMargin, y2 - topMargin};
    return frame;
}

void maybeReverseCorners(Frame& frame) {
    if (rnd.next(0, 1)) {
        swap(frame.ox1, frame.ox2);
        swap(frame.oy1, frame.oy2);
    }
    if (rnd.next(0, 1)) {
        swap(frame.ix1, frame.ix2);
        swap(frame.iy1, frame.iy2);
    }
}

void printFrame(Frame frame) {
    maybeReverseCorners(frame);
    array<long long, 8> values{frame.ox1, frame.oy1, frame.ox2, frame.oy2,
                               frame.ix1, frame.iy1, frame.ix2, frame.iy2};
    println(values.begin(), values.end());
}

bool inBounds(const Frame& frame) {
    array<long long, 8> values{frame.ox1, frame.oy1, frame.ox2, frame.oy2,
                               frame.ix1, frame.iy1, frame.ix2, frame.iy2};
    return all_of(values.begin(), values.end(),
                  [](long long value) { return -kCoordLimit <= value && value <= kCoordLimit; });
}

pair<long long, long long> dimensionsForMode(int mode) {
    if (mode == 0) {
        return {rnd.next(3LL, 8LL), rnd.next(3LL, 8LL)};
    }
    if (mode == 1) {
        return {rnd.next(6LL, 30LL), rnd.next(6LL, 30LL)};
    }
    if (mode == 2) {
        return {rnd.next(3LL, 12LL), rnd.next(20LL, 80LL)};
    }
    if (mode == 3) {
        return {rnd.next(3LL, 1000LL), rnd.next(3LL, 1000LL)};
    }
    return {rnd.next(10LL, 100LL), rnd.next(3LL, 20LL)};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    auto [width1, height1] = dimensionsForMode(mode);
    auto [width2, height2] = dimensionsForMode(rnd.next(0, 4));

    if (mode == 4 && rnd.next(0, 1)) {
        swap(width2, height2);
    }

    Frame first = makeFrame(width1, height1, mode);
    Frame second = makeFrame(width2, height2, rnd.next(0, 4));

    if (rnd.next(0, 2) == 0) {
        long long dx = rnd.next(-20LL, 20LL);
        long long dy = rnd.next(-20LL, 20LL);
        long long shiftX = first.ox1 + dx - second.ox1;
        long long shiftY = first.oy1 + dy - second.oy1;
        Frame shifted = second;
        shifted.ox1 += shiftX;
        shifted.ox2 += shiftX;
        shifted.ix1 += shiftX;
        shifted.ix2 += shiftX;
        shifted.oy1 += shiftY;
        shifted.oy2 += shiftY;
        shifted.iy1 += shiftY;
        shifted.iy2 += shiftY;
        if (inBounds(shifted)) {
            second = shifted;
        }
    }

    printFrame(first);
    printFrame(second);

    return 0;
}
