#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Segment {
    long long x1, y1, x2, y2;
};

long double sweepX;
vector<Segment> segments;

long double yAt(int id) {
    const Segment& s = segments[id];
    return (long double)s.y1 +
           ((long double)(s.y2 - s.y1) * (sweepX - (long double)s.x1)) /
               (long double)(s.x2 - s.x1);
}

struct ByYAtSweepX {
    bool operator()(int a, int b) const {
        if (a == b) {
            return false;
        }
        long double ya = yAt(a);
        long double yb = yAt(b);
        if (ya != yb) {
            return ya < yb;
        }
        return a < b;
    }
};

int sign128(__int128 value) {
    if (value < 0) {
        return -1;
    }
    if (value > 0) {
        return 1;
    }
    return 0;
}

int orientation(const Segment& s, long long x, long long y) {
    __int128 dx1 = (__int128)s.x2 - s.x1;
    __int128 dy1 = (__int128)s.y2 - s.y1;
    __int128 dx2 = (__int128)x - s.x1;
    __int128 dy2 = (__int128)y - s.y1;
    return sign128(dx1 * dy2 - dy1 * dx2);
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool containsPoint(const Segment& s, long long x, long long y) {
    return orientation(s, x, y) == 0 &&
           between(s.x1, s.x2, x) &&
           between(s.y1, s.y2, y);
}

bool intersects(int a, int b) {
    const Segment& p = segments[a];
    const Segment& q = segments[b];

    int o1 = orientation(p, q.x1, q.y1);
    int o2 = orientation(p, q.x2, q.y2);
    int o3 = orientation(q, p.x1, p.y1);
    int o4 = orientation(q, p.x2, p.y2);

    if (o1 == 0 && containsPoint(p, q.x1, q.y1)) {
        return true;
    }
    if (o2 == 0 && containsPoint(p, q.x2, q.y2)) {
        return true;
    }
    if (o3 == 0 && containsPoint(q, p.x1, p.y1)) {
        return true;
    }
    if (o4 == 0 && containsPoint(q, p.x2, p.y2)) {
        return true;
    }
    return o1 != o2 && o3 != o4;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COORD = -1000000;
    const long long MAX_COORD = 1000000;
    const int MAX_N = 100000;

    int n = inf.readInt(0, MAX_N, "N");
    inf.readEoln();

    segments.reserve(n);
    vector<pair<long long, long long>> endpoints;
    endpoints.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        long long x1 = inf.readLong(MIN_COORD, MAX_COORD, "x1");
        inf.readSpace();
        long long y1 = inf.readLong(MIN_COORD, MAX_COORD, "y1");
        inf.readSpace();
        long long x2 = inf.readLong(MIN_COORD, MAX_COORD, "x2");
        inf.readSpace();
        long long y2 = inf.readLong(MIN_COORD, MAX_COORD, "y2");
        inf.readEoln();

        ensuref(x1 != x2, "segment %d is vertical", i + 1);
        ensuref(y1 != y2, "segment %d is horizontal", i + 1);

        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }

        segments.push_back({x1, y1, x2, y2});
        endpoints.push_back({x1, y1});
        endpoints.push_back({x2, y2});
    }

    long long x0 = inf.readLong(MIN_COORD, MAX_COORD, "x0");
    (void)x0;
    inf.readEoln();
    inf.readEof();

    sort(endpoints.begin(), endpoints.end());
    for (int i = 1; i < (int)endpoints.size(); ++i) {
        ensuref(endpoints[i - 1] != endpoints[i],
                "segments share endpoint (%lld, %lld)",
                endpoints[i].first,
                endpoints[i].second);
    }

    struct Event {
        long long x;
        int type;
        int id;
    };

    vector<Event> events;
    events.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        events.push_back({segments[i].x1, 0, i});
        events.push_back({segments[i].x2, 1, i});
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.type < b.type;
    });

    set<int, ByYAtSweepX> active;
    vector<set<int, ByYAtSweepX>::iterator> where(n);

    auto check = [&](set<int, ByYAtSweepX>::iterator a,
                     set<int, ByYAtSweepX>::iterator b) {
        if (a == active.end() || b == active.end()) {
            return;
        }
        ensuref(!intersects(*a, *b),
                "segments %d and %d intersect",
                *a + 1,
                *b + 1);
    };

    for (const Event& event : events) {
        int id = event.id;
        if (event.type == 0) {
            sweepX = nextafter((long double)segments[id].x1,
                               numeric_limits<long double>::infinity());
            auto it = active.insert(id).first;
            where[id] = it;

            if (it != active.begin()) {
                auto previous = prev(it);
                check(previous, it);
            }
            auto nextIt = next(it);
            check(it, nextIt);
        } else {
            sweepX = nextafter((long double)segments[id].x2,
                               -numeric_limits<long double>::infinity());
            auto it = where[id];
            auto previous = it;
            auto nextIt = next(it);
            bool hasPrevious = it != active.begin();
            if (hasPrevious) {
                --previous;
            }

            active.erase(it);

            if (hasPrevious) {
                check(previous, nextIt);
            }
        }
    }
}
