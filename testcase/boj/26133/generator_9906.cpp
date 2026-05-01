#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

struct P {
    int x, y;
};

bool operator==(const P& a, const P& b) {
    return a.x == b.x && a.y == b.y;
}

long long crossLL(long long ax, long long ay, long long bx, long long by) {
    return ax * by - ay * bx;
}

long long polygonArea2(const vector<P>& poly) {
    long long area2 = 0;
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area2 += (long long)poly[i].x * poly[j].y - (long long)poly[j].x * poly[i].y;
    }
    return area2;
}

bool pointOnSegment(const P& a, const P& b, const P& p) {
    long long cross = crossLL(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y);
    if (cross != 0) return false;
    if (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
        min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y))
        return true;
    return false;
}

bool pointOnBoundary(const vector<P>& poly, const P& p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (pointOnSegment(poly[i], poly[j], p)) return true;
    }
    return false;
}

// Strictly inside (not on boundary)
bool pointInPolygonStrict(const vector<P>& poly, const P& p) {
    if (pointOnBoundary(poly, p)) return false;
    bool inside = false;
    int n = (int)poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const P& a = poly[j];
        const P& b = poly[i];
        bool intersect = ((b.y > p.y) != (a.y > p.y));
        if (intersect) {
            double xint = (double)(a.x - b.x) * (p.y - b.y) / (double)(a.y - b.y) + b.x;
            if (xint > p.x)
                inside = !inside;
        }
    }
    return inside;
}

P randomInteriorPoint(const vector<P>& poly) {
    int n = (int)poly.size();
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (const auto& v : poly) {
        minX = min(minX, v.x);
        maxX = max(maxX, v.x);
        minY = min(minY, v.y);
        maxY = max(maxY, v.y);
    }

    // assume polygon has some interior lattice points
    for (int it = 0; it < 100000; ++it) {
        int x = rnd.next(minX + 1, maxX - 1);
        int y = rnd.next(minY + 1, maxY - 1);
        P p{ x, y };
        if (pointInPolygonStrict(poly, p))
            return p;
    }
    // Fallback (should not happen with our shapes): try vertices' centroid rounded
    long long sx = 0, sy = 0;
    for (const auto& v : poly) {
        sx += v.x;
        sy += v.y;
    }
    P c{ (int)(sx / n), (int)(sy / n) };
    if (!pointInPolygonStrict(poly, c)) {
        // tiny adjustment
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy) {
                P q{ c.x + dx, c.y + dy };
                if (pointInPolygonStrict(poly, q)) return q;
            }
    }
    return c; // last resort; assume it's okay
}

void ensureInsideAndDistinct(const vector<P>& poly, P& g, bool hasG, P& s, bool hasS) {
    if (!hasG || !pointInPolygonStrict(poly, g)) {
        g = randomInteriorPoint(poly);
    }
    if (!hasS || !pointInPolygonStrict(poly, s)) {
        do {
            s = randomInteriorPoint(poly);
        } while (s == g);
    } else if (s == g) {
        do {
            s = randomInteriorPoint(poly);
        } while (s == g);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<P> poly;
    P guard{0, 0}, sculpture{0, 0};
    bool guardSet = false, sculptureSet = false;

    // Choose pattern type (biased towards concave)
    vector<int> types = {0, 0, 1, 2, 2, 3, 3, 3};
    int type = rnd.any(types);

    if (type == 0) {
        // Rectangle (convex quad)
        int W = rnd.next(5, 40);
        int H = rnd.next(5, 40);
        poly = {{0,0}, {W,0}, {W,H}, {0,H}};

        int variant = rnd.next(0, 2);
        if (variant == 0) {
            guard = {1, H / 2};
            sculpture = {W - 1, H / 2};
            guardSet = sculptureSet = true;
        } else if (variant == 1) {
            guard = {W / 3, H / 2};
            sculpture = {W / 3 + 1, H / 2 + 1};
            guardSet = sculptureSet = true;
        } // else use randomInterior later
    } else if (type == 1) {
        // Triangle (convex)
        int W = rnd.next(6, 40);
        int H = rnd.next(6, 40);
        poly = {{0,0}, {W,0}, {W/2, H}};
        // use random interior points
    } else if (type == 2) {
        // L-shape (6 vertices)
        int a = rnd.next(3, 15);
        int b = rnd.next(3, 15);
        int W = rnd.next(a + 3, a + 20);
        int H = rnd.next(b + 3, b + 20);
        poly = {
            {0,0},
            {a,0},
            {a,b},
            {W,b},
            {W,H},
            {0,H}
        };
        int variant = rnd.next(0, 1);
        if (variant == 0) {
            // Guard in lower-left pocket, sculpture in upper-right pocket (occluded)
            if (a >= 2 && b >= 2 && W >= a + 2 && H >= b + 2) {
                guard = { rnd.next(1, a - 1), rnd.next(1, b - 1) };
                sculpture = { rnd.next(a + 1, W - 1), rnd.next(b + 1, H - 1) };
                guardSet = sculptureSet = true;
            }
        } else {
            // Both in upper-right
            if (W >= a + 2 && H >= b + 2) {
                guard = { rnd.next(a + 1, W - 1), rnd.next(b + 1, H - 1) };
                sculpture = { rnd.next(a + 1, W - 1), rnd.next(b + 1, H - 1) };
                guardSet = sculptureSet = true;
            }
        }
    } else if (type == 3) {
        // U-shape (8 vertices)
        int W = rnd.next(12, 40);
        int H1 = rnd.next(8, 40);
        int H0 = rnd.next(2, H1 - 3); // ensure H1 - H0 >= 3

        int A = rnd.next(2, max(2, W / 3));
        int B_lo = max(A + 2, 2 * W / 3);
        if (B_lo > W - 2) B_lo = W - 2;
        int B_hi = W - 2;
        if (B_lo > B_hi) {
            B_lo = A + 2;
            B_hi = W - 2;
        }
        int B = rnd.next(B_lo, B_hi);

        poly = {
            {0,0},
            {W,0},
            {W,H0},
            {B,H0},
            {B,H1},
            {A,H1},
            {A,H0},
            {0,H0}
        };

        int variant = rnd.next(0, 1);
        if (variant == 0) {
            // Guard in left upper arm, sculpture in right upper arm (occluded)
            if (A >= 2 && H1 >= H0 + 2 && B <= W - 2) {
                guard = { rnd.next(1, A - 1), rnd.next(H0 + 1, H1 - 1) };
                sculpture = { rnd.next(B + 1, W - 1), rnd.next(H0 + 1, H1 - 1) };
                guardSet = sculptureSet = true;
            }
        } else {
            // Guard bottom center, sculpture in one arm
            if (B >= A + 2 && H0 >= 2) {
                guard = { rnd.next(A + 1, B - 1), rnd.next(1, H0 - 1) };
                sculpture = { rnd.next(1, A - 1), rnd.next(H0 + 1, H1 - 1) };
                guardSet = sculptureSet = true;
            }
        }
    } else {
        // Fallback: rectangle
        int W = rnd.next(5, 40);
        int H = rnd.next(5, 40);
        poly = {{0,0}, {W,0}, {W,H}, {0,H}};
    }

    // Ensure guard and sculpture are valid interior and distinct
    ensureInsideAndDistinct(poly, guard, guardSet, sculpture, sculptureSet);

    // Apply random scaling (keep within some margin before translation)
    int maxX = 0, maxY = 0;
    for (auto& v : poly) {
        maxX = max(maxX, v.x);
        maxY = max(maxY, v.y);
    }
    maxX = max(maxX, max(guard.x, sculpture.x));
    maxY = max(maxY, max(guard.y, sculpture.y));

    vector<int> scales;
    for (int s : {1, 2, 3, 5, 10}) {
        if ((long long)maxX * s <= 900 && (long long)maxY * s <= 900)
            scales.push_back(s);
    }
    int scale = scales.empty() ? 1 : rnd.any(scales);

    if (scale != 1) {
        for (auto& v : poly) { v.x *= scale; v.y *= scale; }
        guard.x *= scale; guard.y *= scale;
        sculpture.x *= scale; sculpture.y *= scale;
    }

    // Optional mirroring within bounding box
    maxX = 0; maxY = 0;
    for (auto& v : poly) {
        maxX = max(maxX, v.x);
        maxY = max(maxY, v.y);
    }
    maxX = max(maxX, max(guard.x, sculpture.x));
    maxY = max(maxY, max(guard.y, sculpture.y));

    bool mirrorX = rnd.next(0, 1);
    bool mirrorY = rnd.next(0, 1);

    if (mirrorX) {
        for (auto& v : poly) v.x = maxX - v.x;
        guard.x = maxX - guard.x;
        sculpture.x = maxX - sculpture.x;
    }
    if (mirrorY) {
        for (auto& v : poly) v.y = maxY - v.y;
        guard.y = maxY - guard.y;
        sculpture.y = maxY - sculpture.y;
    }

    // Translation to fit into [0,1000]
    maxX = 0; maxY = 0;
    int minX = INT_MAX, minY = INT_MAX;
    for (auto& v : poly) {
        maxX = max(maxX, v.x);
        maxY = max(maxY, v.y);
        minX = min(minX, v.x);
        minY = min(minY, v.y);
    }
    maxX = max(maxX, max(guard.x, sculpture.x));
    maxY = max(maxY, max(guard.y, sculpture.y));
    minX = min(minX, min(guard.x, sculpture.x));
    minY = min(minY, min(guard.y, sculpture.y));

    int shiftX = rnd.next(0, 1000 - maxX);
    int shiftY = rnd.next(0, 1000 - maxY);

    for (auto& v : poly) { v.x += shiftX; v.y += shiftY; }
    guard.x += shiftX; guard.y += shiftY;
    sculpture.x += shiftX; sculpture.y += shiftY;

    // Ensure CCW orientation
    if (polygonArea2(poly) < 0) {
        reverse(poly.begin(), poly.end());
    }

    // Randomly rotate polygon vertices (cyclic shift)
    int n = (int)poly.size();
    int shift = rnd.next(0, n - 1);
    if (shift != 0) {
        vector<P> rotated(n);
        for (int i = 0; i < n; ++i)
            rotated[i] = poly[(i + shift) % n];
        poly.swap(rotated);
    }

    // Output
    println(n);
    for (const auto& v : poly) {
        println(v.x, v.y);
    }
    println(guard.x, guard.y);
    println(sculpture.x, sculpture.y);

    return 0;
}
