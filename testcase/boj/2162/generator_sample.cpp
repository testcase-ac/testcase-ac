#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

static int coord(int lo = -20, int hi = 20) {
    return rnd.next(lo, hi);
}

static Segment randomSegment(int lo = -20, int hi = 20) {
    return {coord(lo, hi), coord(lo, hi), coord(lo, hi), coord(lo, hi)};
}

static Segment horizontal(int y, int l, int r) {
    if (l > r) swap(l, r);
    return {l, y, r, y};
}

static Segment vertical(int x, int b, int t) {
    if (b > t) swap(b, t);
    return {x, b, x, t};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<Segment> segments;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int base = i * 3;
            segments.push_back(horizontal(base, -1, 1));
        }
    } else if (mode == 1) {
        int cx = coord(-5, 5);
        int cy = coord(-5, 5);
        for (int i = 0; i < n; ++i) {
            int dx = rnd.next(1, 12);
            int dy = rnd.next(1, 12);
            if (rnd.next(0, 1)) dx = -dx;
            if (rnd.next(0, 1)) dy = -dy;
            segments.push_back({cx - dx, cy - dy, cx + dx, cy + dy});
        }
    } else if (mode == 2) {
        int y = coord(-5, 5);
        int cursor = coord(-10, 0);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(0, 8);
            int gap = rnd.next(0, 3);
            segments.push_back(horizontal(y, cursor, cursor + len));
            cursor += rnd.next(0, len + 1) + gap;
        }
    } else if (mode == 3) {
        int axis = coord(-4, 4);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                segments.push_back(vertical(axis + rnd.next(-1, 1), coord(-12, -1), coord(1, 12)));
            } else {
                segments.push_back(horizontal(axis + rnd.next(-1, 1), coord(-12, -1), coord(1, 12)));
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                int x = coord();
                int y = coord();
                segments.push_back({x, y, x, y});
            } else {
                segments.push_back(randomSegment());
            }
        }
    }

    shuffle(segments.begin(), segments.end());

    println(static_cast<int>(segments.size()));
    for (const Segment& s : segments) {
        println(s.x1, s.y1, s.x2, s.y2);
    }

    return 0;
}
