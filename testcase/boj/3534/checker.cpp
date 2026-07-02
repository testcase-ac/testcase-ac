#include "testlib.h"

#include <algorithm>

using namespace std;

const long long MAX_COORD = 1000000000000000000LL;
const long long MAX_AREA = 40000000000000000LL;

struct Rect {
    long long x1, y1, x2, y2;
};

struct Frame {
    Rect outer;
    Rect inner;
};

struct Answer {
    long long claimedArea;
    long long x;
    long long y;
    long long actualArea;
};

Rect normalize(Rect r) {
    if (r.x1 > r.x2) {
        swap(r.x1, r.x2);
    }
    if (r.y1 > r.y2) {
        swap(r.y1, r.y2);
    }
    return r;
}

Rect translated(Rect r, long long dx, long long dy) {
    r.x1 += dx;
    r.x2 += dx;
    r.y1 += dy;
    r.y2 += dy;
    return r;
}

long long intersectionArea(const Rect& a, const Rect& b) {
    long long width = max(0LL, min(a.x2, b.x2) - max(a.x1, b.x1));
    long long height = max(0LL, min(a.y2, b.y2) - max(a.y1, b.y1));
    return width * height;
}

long long frameIntersectionArea(const Frame& first, const Frame& second, long long dx, long long dy) {
    Frame moved = {translated(second.outer, dx, dy), translated(second.inner, dx, dy)};
    long long area = intersectionArea(first.outer, moved.outer);
    area -= intersectionArea(first.outer, moved.inner);
    area -= intersectionArea(first.inner, moved.outer);
    area += intersectionArea(first.inner, moved.inner);
    return area;
}

Frame readFrame() {
    Rect outer;
    Rect inner;
    outer.x1 = inf.readLong();
    outer.y1 = inf.readLong();
    outer.x2 = inf.readLong();
    outer.y2 = inf.readLong();
    inner.x1 = inf.readLong();
    inner.y1 = inf.readLong();
    inner.x2 = inf.readLong();
    inner.y2 = inf.readLong();
    return {normalize(outer), normalize(inner)};
}

Answer readAnswer(InStream& stream, const Frame& first, const Frame& second) {
    long long claimedArea = stream.readLong(0, MAX_AREA, "area");
    long long x = stream.readLong(-MAX_COORD, MAX_COORD, "x");
    long long y = stream.readLong(-MAX_COORD, MAX_COORD, "y");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after translation vector");
    }

    long long actualArea = frameIntersectionArea(first, second, x, y);
    if (claimedArea != actualArea) {
        stream.quitf(_wa,
                     "claimed area %lld does not match translation area %lld for vector (%lld, %lld)",
                     claimedArea,
                     actualArea,
                     x,
                     y);
    }
    return {claimedArea, x, y, actualArea};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Frame first = readFrame();
    Frame second = readFrame();

    Answer jury = readAnswer(ans, first, second);
    Answer participant = readAnswer(ouf, first, second);

    if (participant.actualArea < jury.actualArea) {
        quitf(_wa,
              "jury has better area: jury=%lld participant=%lld",
              jury.actualArea,
              participant.actualArea);
    }
    if (participant.actualArea > jury.actualArea) {
        quitf(_fail,
              "participant found better area: jury=%lld participant=%lld",
              jury.actualArea,
              participant.actualArea);
    }

    quitf(_ok, "area=%lld", participant.actualArea);
}
