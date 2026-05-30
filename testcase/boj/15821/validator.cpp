#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

int sign(long long value) {
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}

bool boxesIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    return max(a.x, b.x) >= min(c.x, d.x) &&
           max(c.x, d.x) >= min(a.x, b.x) &&
           max(a.y, b.y) >= min(c.y, d.y) &&
           max(c.y, d.y) >= min(a.y, b.y);
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    int abC = sign(cross(a, b, c));
    int abD = sign(cross(a, b, d));
    int cdA = sign(cross(c, d, a));
    int cdB = sign(cross(c, d, b));

    if (abC == 0 && abD == 0) {
        return boxesIntersect(a, b, c, d);
    }

    return abC * abD <= 0 && cdA * cdB <= 0;
}

bool pointOnSegment(const Point& p, const Point& a, const Point& b) {
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool pointInsidePolygon(const Point& p, const vector<Point>& polygon) {
    bool inside = false;
    int n = (int)polygon.size();

    for (int i = 0, j = n - 1; i < n; j = i++) {
        const Point& a = polygon[i];
        const Point& b = polygon[j];

        if (pointOnSegment(p, a, b)) {
            return false;
        }

        if ((a.y > p.y) != (b.y > p.y)) {
            long double xAtY = (long double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
            if (xAtY > p.x) {
                inside = !inside;
            }
        }
    }

    return inside;
}

struct Box {
    long long minX;
    long long maxX;
    long long minY;
    long long maxY;
};

Box boundsOf(const vector<Point>& polygon) {
    Box box{LLONG_MAX, LLONG_MIN, LLONG_MAX, LLONG_MIN};
    for (const Point& p : polygon) {
        box.minX = min(box.minX, p.x);
        box.maxX = max(box.maxX, p.x);
        box.minY = min(box.minY, p.y);
        box.maxY = max(box.maxY, p.y);
    }
    return box;
}

bool boxesIntersect(const Box& a, const Box& b) {
    return a.maxX >= b.minX && b.maxX >= a.minX &&
           a.maxY >= b.minY && b.maxY >= a.minY;
}

bool polygonsIntersectOrOverlap(const vector<Point>& a, const vector<Point>& b) {
    for (int i = 0; i < (int)a.size(); ++i) {
        Point a1 = a[i];
        Point a2 = a[(i + 1) % a.size()];
        for (int j = 0; j < (int)b.size(); ++j) {
            Point b1 = b[j];
            Point b2 = b[(j + 1) % b.size()];
            if (segmentsIntersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }

    return pointInsidePolygon(a[0], b) || pointInsidePolygon(b[0], a);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long coordMin = -100000;
    const long long coordMax = 100000;

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    vector<vector<Point>> polygons;
    vector<Box> boxes;
    polygons.reserve(n);
    boxes.reserve(n);

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);

        int p = inf.readInt(3, 20, "P_i");
        inf.readEoln();

        vector<Point> polygon(p);
        for (int j = 0; j < p; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            polygon[j].x = inf.readLong(coordMin, coordMax, "x");
            inf.readSpace();
            polygon[j].y = inf.readLong(coordMin, coordMax, "y");
        }
        inf.readEoln();

        long long area2 = 0;
        for (int j = 0; j < p; ++j) {
            const Point& a = polygon[j];
            const Point& b = polygon[(j + 1) % p];
            ensuref(!(a.x == b.x && a.y == b.y),
                    "polygon %d has a zero-length edge at vertex %d", i + 1, j + 1);
            area2 += cross(a, b);
        }
        ensuref(area2 != 0, "polygon %d has zero area", i + 1);

        for (int a = 0; a < p; ++a) {
            int aNext = (a + 1) % p;
            for (int b = a + 1; b < p; ++b) {
                int bNext = (b + 1) % p;

                if (aNext == b || bNext == a) {
                    continue;
                }

                ensuref(!segmentsIntersect(polygon[a], polygon[aNext], polygon[b], polygon[bNext]),
                        "polygon %d has intersecting non-adjacent edges %d-%d and %d-%d",
                        i + 1, a + 1, aNext + 1, b + 1, bNext + 1);
            }
        }

        Box box = boundsOf(polygon);
        for (int previous = 0; previous < (int)polygons.size(); ++previous) {
            if (!boxesIntersect(box, boxes[previous])) {
                continue;
            }
            ensuref(!polygonsIntersectOrOverlap(polygon, polygons[previous]),
                    "polygons %d and %d overlap or intersect", previous + 1, i + 1);
        }

        polygons.push_back(polygon);
        boxes.push_back(box);
    }

    inf.readEof();
}
