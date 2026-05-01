#include "testlib.h"
using namespace std;

struct Point {
    long long x, y;
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

vector<Point> convexHullStrict(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }), pts.end());
    int n = (int)pts.size();
    if (n < 3) return {};

    vector<Point> H;
    H.reserve(n * 2);

    // lower hull
    for (int i = 0; i < n; ++i) {
        while (H.size() >= 2 && cross(H[H.size() - 2], H[H.size() - 1], pts[i]) <= 0)
            H.pop_back();
        H.push_back(pts[i]);
    }
    // upper hull
    int lowerSize = (int)H.size();
    for (int i = n - 2; i >= 0; --i) {
        while ((int)H.size() > lowerSize && cross(H[H.size() - 2], H[H.size() - 1], pts[i]) <= 0)
            H.pop_back();
        H.push_back(pts[i]);
    }
    if (H.size() <= 1) return {};
    H.pop_back(); // last is same as first
    if ((int)H.size() < 3) return {};
    return H; // CCW, strictly convex (no collinear adjacent vertices)
}

vector<Point> randomHull(int minPts, int maxPts, int xmin, int xmax, int ymin, int ymax) {
    while (true) {
        int M = rnd.next(minPts, maxPts);
        set<pair<int,int>> S;
        while ((int)S.size() < M) {
            int x = rnd.next(xmin, xmax);
            int y = rnd.next(ymin, ymax);
            S.insert({x, y});
        }
        vector<Point> pts;
        pts.reserve(S.size());
        for (auto &p : S) pts.push_back({p.first, p.second});
        vector<Point> hull = convexHullStrict(pts);
        if ((int)hull.size() >= 3) return hull;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> poly;
    int type = rnd.next(0, 6);

    if (type == 0) {
        // Small random convex polygon
        poly = randomHull(3, 12, -20, 20, -20, 20);
    } else if (type == 1) {
        // Medium random convex polygon (more vertices)
        poly = randomHull(8, 20, -20, 20, -20, 20);
    } else if (type == 2) {
        // Random scalene triangle
        while (true) {
            Point p0{rnd.next(-20, 20), rnd.next(-20, 20)};
            Point p1{rnd.next(-20, 20), rnd.next(-20, 20)};
            Point p2{rnd.next(-20, 20), rnd.next(-20, 20)};
            // ensure distinct
            if ((p0.x == p1.x && p0.y == p1.y) ||
                (p0.x == p2.x && p0.y == p2.y) ||
                (p1.x == p2.x && p1.y == p2.y)) continue;
            long long c = cross(p0, p1, p2);
            if (c == 0) continue; // collinear, resample
            if (c > 0) {
                poly = {p0, p1, p2};
            } else {
                poly = {p0, p2, p1};
            }
            break;
        }
    } else if (type == 3) {
        // Isosceles triangle symmetric about a vertical line (guaranteed YES)
        int w = rnd.next(1, 10);
        int h = rnd.next(1, 10);
        int dx = rnd.next(-10, 10);
        int dy = rnd.next(-10, 10);
        Point top{dx, dy + h};
        Point left{dx - w, dy};
        Point right{dx + w, dy};
        // (top, left, right) is CCW
        poly = {top, left, right};
    } else if (type == 4) {
        // Parallelogram with moderate coordinates (centrally symmetric, YES)
        int ox = rnd.next(-20, 20);
        int oy = rnd.next(-20, 20);
        Point v, u;
        while (true) {
            v = {rnd.next(-10, 10), rnd.next(-10, 10)};
            u = {rnd.next(-10, 10), rnd.next(-10, 10)};
            if ((v.x == 0 && v.y == 0) || (u.x == 0 && u.y == 0)) continue;
            if (v.x * u.y - v.y * u.x != 0) break; // non-collinear
        }
        Point p0{ox, oy};
        Point p1{ox + v.x, oy + v.y};
        Point p2{ox + v.x + u.x, oy + v.y + u.y};
        Point p3{ox + u.x, oy + u.y};
        long long c = cross(p0, p1, p2);
        if (c > 0) {
            poly = {p0, p1, p2, p3};
        } else {
            poly = {p0, p3, p2, p1};
        }
    } else if (type == 5) {
        // Large rectangle near coordinate bounds (centrally symmetric, YES)
        int ox = -10000000 + rnd.next(0, 1000000); // [-1e7, -9e6]
        int oy = -10000000 + rnd.next(0, 1000000);
        int w = rnd.next(1000000, 9000000);
        int h = rnd.next(1000000, 9000000);
        Point p0{ox, oy};
        Point p1{ox + w, oy};
        Point p2{ox + w, oy + h};
        Point p3{ox, oy + h};
        poly = {p0, p1, p2, p3}; // CCW
    } else if (type == 6) {
        // Very slender random convex polygon (precision / edge-case)
        poly = randomHull(5, 15, 0, 100, -2, 2);
    }

    int N = (int)poly.size();
    println(N);
    for (const auto& p : poly) {
        println(p.x, p.y);
    }

    return 0;
}
