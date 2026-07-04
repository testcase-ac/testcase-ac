#include "testlib.h"

#include <algorithm>
#include <array>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

struct Segment {
    Point a;
    Point b;
};

static bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

static bool isEndpoint(const Segment& s, Point p) {
    return s.a == p || s.b == p;
}

static bool containsPoint(const Segment& s, Point p) {
    if (s.a.x == s.b.x) {
        return p.x == s.a.x && min(s.a.y, s.b.y) <= p.y && p.y <= max(s.a.y, s.b.y);
    }
    return p.y == s.a.y && min(s.a.x, s.b.x) <= p.x && p.x <= max(s.a.x, s.b.x);
}

static bool validSegment(const vector<Segment>& segments, const Segment& candidate) {
    if (candidate.a == candidate.b) {
        return false;
    }
    if (candidate.a.x != candidate.b.x && candidate.a.y != candidate.b.y) {
        return false;
    }

    int lx = min(candidate.a.x, candidate.b.x);
    int rx = max(candidate.a.x, candidate.b.x);
    int ly = min(candidate.a.y, candidate.b.y);
    int ry = max(candidate.a.y, candidate.b.y);
    for (const Segment& existing : segments) {
        int elx = min(existing.a.x, existing.b.x);
        int erx = max(existing.a.x, existing.b.x);
        int ely = min(existing.a.y, existing.b.y);
        int ery = max(existing.a.y, existing.b.y);
        if (candidate.a.y == candidate.b.y && existing.a.y == existing.b.y &&
            candidate.a.y == existing.a.y && max(lx, elx) < min(rx, erx)) {
            return false;
        }
        if (candidate.a.x == candidate.b.x && existing.a.x == existing.b.x &&
            candidate.a.x == existing.a.x && max(ly, ely) < min(ry, ery)) {
            return false;
        }
        for (int x = max(lx, elx); x <= min(rx, erx); ++x) {
            for (int y = max(ly, ely); y <= min(ry, ery); ++y) {
                Point p{x, y};
                if (containsPoint(candidate, p) && containsPoint(existing, p) &&
                    (!isEndpoint(candidate, p) || !isEndpoint(existing, p))) {
                    return false;
                }
            }
        }
    }
    return true;
}

static bool addSegment(vector<Segment>& segments, Point a, Point b) {
    Segment candidate{a, b};
    if (!validSegment(segments, candidate)) {
        return false;
    }
    segments.push_back(candidate);
    return true;
}

static Point randomPoint(int lo, int hi) {
    return Point{rnd.next(lo, hi), rnd.next(lo, hi)};
}

static Point randomOffsetPoint(Point from) {
    vector<Point> candidates;
    for (int len = 1; len <= 8; ++len) {
        if (from.x + len <= 300) {
            candidates.push_back(Point{from.x + len, from.y});
        }
        if (from.x - len >= 0) {
            candidates.push_back(Point{from.x - len, from.y});
        }
        if (from.y + len <= 300) {
            candidates.push_back(Point{from.x, from.y + len});
        }
        if (from.y - len >= 0) {
            candidates.push_back(Point{from.x, from.y - len});
        }
    }
    return rnd.any(candidates);
}

static vector<Point> endpointsOf(const vector<Segment>& segments) {
    vector<Point> points;
    for (const Segment& segment : segments) {
        points.push_back(segment.a);
        points.push_back(segment.b);
    }
    return points;
}

static void addRandomWalk(vector<Segment>& segments, Point start, int steps) {
    Point current = start;
    for (int i = 0; i < steps; ++i) {
        bool added = false;
        for (int attempt = 0; attempt < 80 && !added; ++attempt) {
            Point next = randomOffsetPoint(current);
            if (addSegment(segments, current, next)) {
                current = next;
                added = true;
            }
        }
        if (!added) {
            return;
        }
    }
}

static void addBranch(vector<Segment>& segments, int count) {
    for (int i = 0; i < count; ++i) {
        vector<Point> endpoints = endpointsOf(segments);
        shuffle(endpoints.begin(), endpoints.end());
        bool added = false;
        for (Point base : endpoints) {
            for (int attempt = 0; attempt < 40 && !added; ++attempt) {
                added = addSegment(segments, base, randomOffsetPoint(base));
            }
            if (added) {
                break;
            }
        }
    }
}

static bool addRectangle(vector<Segment>& segments, Point low, int width, int height) {
    Point a{low.x, low.y};
    Point b{low.x + width, low.y};
    Point c{low.x + width, low.y + height};
    Point d{low.x, low.y + height};
    int oldSize = int(segments.size());
    if (addSegment(segments, a, b) && addSegment(segments, b, c) &&
        addSegment(segments, c, d) && addSegment(segments, d, a)) {
        return true;
    }
    segments.resize(oldSize);
    return false;
}

static void addDistractors(vector<Segment>& segments, int count) {
    for (int i = 0; i < count; ++i) {
        for (int attempt = 0; attempt < 120; ++attempt) {
            Point a = randomPoint(0, 300);
            Point b = rnd.next(2) == 0 ? Point{rnd.next(0, 300), a.y} : Point{a.x, rnd.next(0, 300)};
            if (addSegment(segments, a, b)) {
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Segment> segments;
    int mode = rnd.next(0, 4);
    Point target{0, 0};

    if (mode == 0) {
        Point start = randomPoint(0, 300);
        addSegment(segments, start, randomOffsetPoint(start));
    } else if (mode == 1) {
        addRandomWalk(segments, randomPoint(20, 280), rnd.next(3, 9));
    } else if (mode == 2) {
        Point low{rnd.next(0, 270), rnd.next(0, 270)};
        addRectangle(segments, low, rnd.next(2, 12), rnd.next(2, 12));
        addBranch(segments, rnd.next(1, 4));
    } else {
        addRandomWalk(segments, randomPoint(30, 270), rnd.next(2, 6));
        addBranch(segments, rnd.next(2, 8));
    }

    if (segments.empty()) {
        addSegment(segments, Point{0, 0}, Point{1, 0});
    }

    Segment targetSegment = rnd.any(segments);
    if (targetSegment.a.x == targetSegment.b.x) {
        target = Point{targetSegment.a.x, rnd.next(min(targetSegment.a.y, targetSegment.b.y),
                                                   max(targetSegment.a.y, targetSegment.b.y))};
    } else {
        target = Point{rnd.next(min(targetSegment.a.x, targetSegment.b.x),
                                max(targetSegment.a.x, targetSegment.b.x)),
                       targetSegment.a.y};
    }

    addDistractors(segments, rnd.next(0, 5));
    shuffle(segments.begin(), segments.end());

    println(int(segments.size()));
    for (const Segment& segment : segments) {
        println(segment.a.x, segment.a.y, segment.b.x, segment.b.y);
    }
    println(target.x, target.y);
    return 0;
}
