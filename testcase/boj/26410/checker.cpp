#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const long long COORD_LIMIT = 1000000000LL;
const long double PI = acosl(-1.0L);
const long double EPS = 1e-13L;

struct Point {
    long long x;
    long long y;
};

__int128 cross(const Point& a, const Point& b, const Point& c) {
    __int128 ux = (__int128)b.x - a.x;
    __int128 uy = (__int128)b.y - a.y;
    __int128 vx = (__int128)c.x - a.x;
    __int128 vy = (__int128)c.y - a.y;
    return ux * vy - uy * vx;
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

long double normalizeLineAngle(long double angle) {
    angle = fmodl(angle, PI);
    if (angle < 0) {
        angle += PI;
    }
    if (angle >= PI - EPS) {
        angle = 0;
    }
    return angle;
}

bool sameAngle(long double a, long double b) {
    return fabsl(a - b) <= EPS || fabsl(fabsl(a - b) - PI) <= EPS;
}

bool isTangentLine(const vector<Point>& polygon, const Point& q, long double theta, bool qOnBoundary) {
    long double dx = cosl(theta);
    long double dy = sinl(theta);
    bool hasPositive = false;
    bool hasNegative = false;
    bool touchesBoundary = qOnBoundary;

    for (const Point& p : polygon) {
        if (p.x == q.x && p.y == q.y) {
            touchesBoundary = true;
            continue;
        }

        long double value = dx * ((long double)p.y - q.y) - dy * ((long double)p.x - q.x);
        if (value > 1e-8L) {
            hasPositive = true;
        } else if (value < -1e-8L) {
            hasNegative = true;
        } else {
            touchesBoundary = true;
        }
    }

    return touchesBoundary && !(hasPositive && hasNegative);
}

bool hasPerpendicularTangents(const vector<Point>& polygon, const Point& q) {
    bool qOnBoundary = false;
    int n = (int)polygon.size();
    for (int i = 0; i < n; ++i) {
        if (onSegment(polygon[i], polygon[(i + 1) % n], q)) {
            qOnBoundary = true;
            break;
        }
    }

    vector<long double> candidates;
    candidates.push_back(0);
    candidates.push_back(PI / 2);

    for (const Point& p : polygon) {
        if (p.x == q.x && p.y == q.y) {
            continue;
        }
        long double angle = normalizeLineAngle(atan2l((long double)p.y - q.y, (long double)p.x - q.x));
        candidates.push_back(angle);
        candidates.push_back(normalizeLineAngle(angle + PI / 2));
        candidates.push_back(normalizeLineAngle(angle - PI / 2));
    }

    sort(candidates.begin(), candidates.end());
    vector<long double> uniqueAngles;
    for (long double angle : candidates) {
        if (uniqueAngles.empty() || !sameAngle(uniqueAngles.back(), angle)) {
            uniqueAngles.push_back(angle);
        }
    }
    if (uniqueAngles.size() >= 2 && sameAngle(uniqueAngles.front() + PI, uniqueAngles.back())) {
        uniqueAngles.pop_back();
    }

    int m = (int)uniqueAngles.size();
    for (int i = 0; i < m; ++i) {
        long double a = uniqueAngles[i];
        long double b = uniqueAngles[(i + 1) % m];
        long double gap = b - a;
        if (i + 1 == m) {
            gap += PI;
        }
        if (gap > EPS) {
            candidates.push_back(normalizeLineAngle(a + gap / 2));
        }
    }

    for (long double theta : candidates) {
        theta = normalizeLineAngle(theta);
        if (isTangentLine(polygon, q, theta, qOnBoundary) &&
            isTangentLine(polygon, q, normalizeLineAngle(theta + PI / 2), qOnBoundary)) {
            return true;
        }
    }

    return false;
}

Point readAnswer(InStream& stream, const vector<Point>& polygon) {
    Point q;
    q.x = stream.readLong(-COORD_LIMIT, COORD_LIMIT, "x");
    stream.readSpace();
    q.y = stream.readLong(-COORD_LIMIT, COORD_LIMIT, "y");
    stream.readEoln();
    stream.readEof();

    if (!hasPerpendicularTangents(polygon, q)) {
        stream.quitf(_wa, "point (%lld, %lld) does not have two perpendicular tangents", q.x, q.y);
    }
    return q;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<Point> polygon(n);
    for (int i = 0; i < n; ++i) {
        polygon[i].x = inf.readLong();
        polygon[i].y = inf.readLong();
    }

    Point jury = readAnswer(ans, polygon);
    Point participant = readAnswer(ouf, polygon);

    quitf(_ok,
          "accepted point (%lld, %lld), jury point (%lld, %lld)",
          participant.x,
          participant.y,
          jury.x,
          jury.y);
}
