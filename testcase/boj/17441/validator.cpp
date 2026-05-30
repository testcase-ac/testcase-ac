#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Segment {
    Point a;
    Point b;
    int id;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    return x1 * y2 - y1 * x2;
}

int sign(long long v) {
    return (v > 0) - (v < 0);
}

bool intersects(const Segment& s, const Segment& t) {
    long long c1 = cross(s.a, s.b, t.a);
    long long c2 = cross(s.a, s.b, t.b);
    long long c3 = cross(t.a, t.b, s.a);
    long long c4 = cross(t.a, t.b, s.b);

    if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) {
        return max(min(s.a.x, s.b.x), min(t.a.x, t.b.x)) <=
                   min(max(s.a.x, s.b.x), max(t.a.x, t.b.x)) &&
               max(min(s.a.y, s.b.y), min(t.a.y, t.b.y)) <=
                   min(max(s.a.y, s.b.y), max(t.a.y, t.b.y));
    }

    return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
}

bool adjacent(int a, int b, int n) {
    int d = abs(a - b);
    return d == 1 || d == n - 1;
}

bool hasInvalidIntersectionSlow(const vector<Segment>& segments, int& first, int& second) {
    int n = (int)segments.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacent(i, j, n)) {
                continue;
            }
            if (intersects(segments[i], segments[j])) {
                first = i;
                second = j;
                return true;
            }
        }
    }
    return false;
}

long double sweepX;

long double yAt(const Segment& s, long double x) {
    if (s.a.x == s.b.x) {
        return min(s.a.y, s.b.y);
    }
    return s.a.y + (long double)(s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
}

bool hasInvalidIntersectionSweep(const vector<Segment>& segments, int& first, int& second) {
    struct Event {
        long long x;
        int type;
        int id;
    };

    vector<Event> events;
    events.reserve(2 * segments.size());
    for (const Segment& s : segments) {
        long long lx = min(s.a.x, s.b.x);
        long long rx = max(s.a.x, s.b.x);
        events.push_back({lx, 0, s.id});
        events.push_back({rx, 1, s.id});
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.type != b.type) return a.type < b.type;
        return a.id < b.id;
    });

    auto cmp = [&](int a, int b) {
        long double ya = yAt(segments[a], sweepX);
        long double yb = yAt(segments[b], sweepX);
        if (fabsl(ya - yb) > 1e-18L) return ya < yb;
        return a < b;
    };

    set<int, decltype(cmp)> active(cmp);

    auto badPair = [&](int a, int b) {
        if (a < 0 || b < 0 || adjacent(a, b, (int)segments.size())) {
            return false;
        }
        if (!intersects(segments[a], segments[b])) {
            return false;
        }
        first = min(a, b);
        second = max(a, b);
        return true;
    };

    for (const Event& event : events) {
        sweepX = event.x;
        int id = event.id;
        if (event.type == 0) {
            auto it = active.insert(id).first;
            if (it != active.begin()) {
                auto prevIt = prev(it);
                if (badPair(*prevIt, *it)) return true;
            }
            auto nextIt = next(it);
            if (nextIt != active.end() && badPair(*it, *nextIt)) return true;
        } else {
            auto it = active.find(id);
            if (it == active.end()) {
                continue;
            }
            auto prevIt = it == active.begin() ? active.end() : prev(it);
            auto nextIt = next(it);
            if (prevIt != active.end() && nextIt != active.end() && badPair(*prevIt, *nextIt)) {
                return true;
            }
            active.erase(it);
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].x = inf.readLong(-10000LL, 10000LL, "x_i");
        inf.readSpace();
        p[i].y = inf.readLong(-10000LL, 10000LL, "y_i");
        inf.readEoln();
    }

    vector<Segment> segments;
    segments.reserve(n);
    __int128 area2 = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ensuref(p[i].x != p[j].x || p[i].y != p[j].y,
                "consecutive vertices %d and %d are equal", i + 1, j + 1);
        area2 += (__int128)p[i].x * p[j].y - (__int128)p[j].x * p[i].y;
        segments.push_back({p[i], p[j], i});
    }

    ensuref(area2 > 0, "polygon vertices must be given in counterclockwise order");

    int first = -1;
    int second = -1;
    bool hasInvalidIntersection = n <= 5000
        ? hasInvalidIntersectionSlow(segments, first, second)
        : hasInvalidIntersectionSweep(segments, first, second);
    ensuref(!hasInvalidIntersection,
            "non-adjacent edges %d and %d intersect", first + 1, second + 1);

    inf.readEof();
}
