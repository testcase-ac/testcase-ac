#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Segment {
    Point a;
    Point b;
};

Point makePoint(long long x, long long y, long long scale) {
    return {x * scale, y * scale};
}

Segment makeSegment(long long x1, long long y1, long long x2, long long y2) {
    long long s1 = rnd.next(1, 20);
    long long s2 = rnd.next(1, 20);
    Point a = makePoint(x1, y1, s1);
    Point b = makePoint(x2, y2, s2);
    if (a.x == b.x && a.y == b.y) {
        b.x += 1;
    }
    if (rnd.next(2)) {
        swap(a, b);
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 35);
    if (mode == 5) {
        n = rnd.next(36, 90);
    }

    vector<Segment> segments;
    segments.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            long long low = rnd.next(1, 20);
            long long high = rnd.next(low + 1, low + 25);
            segments.push_back(makeSegment(low, 1, high, 1));
        }
    } else if (mode == 1) {
        long long center = rnd.next(2, 18);
        for (int i = 0; i < n; ++i) {
            long long left = max(1LL, center - rnd.next(0, 5));
            long long right = center + rnd.next(0, 5);
            if (left == right) {
                ++right;
            }
            segments.push_back(makeSegment(left, 1, right, 1));
        }
    } else if (mode == 2) {
        vector<pair<long long, long long>> slopes = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2}, {3, 5}, {5, 3}};
        for (int i = 0; i < n; ++i) {
            auto s1 = rnd.any(slopes);
            auto s2 = rnd.any(slopes);
            if (s1 == s2) {
                s2 = slopes[(find(slopes.begin(), slopes.end(), s1) - slopes.begin() + 1) % slopes.size()];
            }
            segments.push_back(makeSegment(s1.first, s1.second, s2.first, s2.second));
        }
    } else if (mode == 3) {
        Segment base = makeSegment(1, 2, 4, 3);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                segments.push_back(base);
            } else {
                segments.push_back(makeSegment(rnd.next(1, 12), rnd.next(1, 12), rnd.next(1, 12), rnd.next(1, 12)));
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            long long x1 = rnd.next(1, 1000000000);
            long long y1 = rnd.next(1, 30);
            long long x2 = rnd.next(1, 30);
            long long y2 = rnd.next(1, 1000000000);
            if (x1 == x2 && y1 == y2) {
                y2 = y2 == 1000000000 ? y2 - 1 : y2 + 1;
            }
            if (rnd.next(2)) {
                swap(x1, x2);
                swap(y1, y2);
            }
            segments.push_back({{x1, y1}, {x2, y2}});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long x1 = rnd.next(1, 60);
            long long y1 = rnd.next(1, 60);
            long long x2 = rnd.next(1, 60);
            long long y2 = rnd.next(1, 60);
            if (x1 == x2 && y1 == y2) {
                x2 = x2 == 60 ? x2 - 1 : x2 + 1;
            }
            segments.push_back({{x1, y1}, {x2, y2}});
        }
    }

    shuffle(segments.begin(), segments.end());

    println(n);
    for (const Segment& s : segments) {
        println(s.a.x, s.a.y, s.b.x, s.b.y);
    }

    return 0;
}
