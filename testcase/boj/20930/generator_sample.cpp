#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Segment {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

Segment makeSegment(long long cx, long long cy, int dx, int dy) {
    if (dx == 0 && dy == 0) dx = 1;
    Segment s{cx - dx, cy - dy, cx + dx, cy + dy};
    if (rnd.next(2)) {
        swap(s.x1, s.x2);
        swap(s.y1, s.y2);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    int q = rnd.next(1, 20);
    vector<Segment> segments;

    if (mode == 0) {
        long long x = rnd.next(-8, 8);
        long long y = rnd.next(-8, 8);
        for (int i = 0; i < n; ++i) {
            int dx = rnd.next(0, 4);
            int dy = rnd.next(0, 4);
            segments.push_back(makeSegment(x + i, y + rnd.next(-2, 2), dx + 1, dy));
        }
    } else if (mode == 1) {
        int first = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            long long base = (i < first ? 0 : 40);
            long long cx = base + rnd.next(-6, 6);
            long long cy = base + rnd.next(-6, 6);
            segments.push_back(makeSegment(cx, cy, rnd.next(0, 3), rnd.next(0, 3)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            long long x1 = rnd.next(-12, 12);
            long long y1 = rnd.next(-12, 12);
            if (rnd.next(2)) {
                segments.push_back({x1, y1, x1 + rnd.next(1, 8), y1});
            } else {
                segments.push_back({x1, y1, x1, y1 + rnd.next(1, 8)});
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long cx = (i % 3) * 7 + rnd.next(-2, 2);
            long long cy = (i / 3) * 7 + rnd.next(-2, 2);
            segments.push_back(makeSegment(cx, cy, rnd.next(1, 5), rnd.next(1, 5)));
        }
    } else {
        segments.push_back({-1000000000LL, 1000000000LL, 1000000000LL, -1000000000LL});
        while ((int)segments.size() < n) {
            long long cx = rnd.next(-20, 20);
            long long cy = rnd.next(-20, 20);
            segments.push_back(makeSegment(cx, cy, rnd.next(0, 6), rnd.next(0, 6)));
        }
    }

    shuffle(segments.begin(), segments.end());

    println(n, q);
    for (const Segment& s : segments) {
        println(s.x1, s.y1, s.x2, s.y2);
    }

    for (int i = 0; i < q; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        println(a, b);
    }

    return 0;
}
