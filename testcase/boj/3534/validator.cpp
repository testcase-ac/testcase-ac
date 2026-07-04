#include "testlib.h"

#include <algorithm>
#include <array>

using namespace std;

namespace {

constexpr long long kCoordLimit = 100000000LL;

struct Rect {
    long long minX;
    long long maxX;
    long long minY;
    long long maxY;
};

Rect normalize(long long x1, long long y1, long long x2, long long y2) {
    return {min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2)};
}

void validateFrame(int frameIndex) {
    array<long long, 8> value{};
    for (int i = 0; i < 8; ++i) {
        value[i] = inf.readLong(-kCoordLimit, kCoordLimit, format("frame%d_coord%d", frameIndex, i + 1));
        if (i + 1 < 8) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    Rect outer = normalize(value[0], value[1], value[2], value[3]);
    Rect inner = normalize(value[4], value[5], value[6], value[7]);

    ensuref(outer.minX < outer.maxX && outer.minY < outer.maxY,
            "frame %d outer rectangle must have positive width and height", frameIndex);
    ensuref(inner.minX < inner.maxX && inner.minY < inner.maxY,
            "frame %d inner rectangle must have positive width and height", frameIndex);
    ensuref(outer.minX < inner.minX && inner.maxX < outer.maxX &&
                    outer.minY < inner.minY && inner.maxY < outer.maxY,
            "frame %d inner rectangle must lie strictly inside the outer rectangle", frameIndex);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    validateFrame(1);
    validateFrame(2);

    inf.readEof();
}
