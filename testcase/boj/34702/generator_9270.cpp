#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Pt {
    long long x, y;
};

long long cross(const Pt& o, const Pt& a, const Pt& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

vector<Pt> convexHull(vector<Pt> pts) {
    int n = (int)pts.size();
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    if (n <= 1) return pts;
    vector<Pt> lower, upper;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower[lower.size() - 1], pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper[upper.size() - 1], pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower; // CCW, strictly convex, no three collinear
}

bool onSegment(const Pt& a, const Pt& b, const Pt& p) {
    if (cross(a, b, p) != 0) return false;
    long long minx = min(a.x, b.x), maxx = max(a.x, b.x);
    long long miny = min(a.y, b.y), maxy = max(a.y, b.y);
    return (p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy);
}

bool isOnBoundary(const vector<Pt>& poly, const Pt& p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        const Pt& a = poly[i];
        const Pt& b = poly[(i + 1) % n];
        if (onSegment(a, b, p)) return true;
    }
    return false;
}

bool isInsideStrict(const vector<Pt>& poly, const Pt& p) {
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        const Pt& a = poly[i];
        const Pt& b = poly[(i + 1) % n];
        long long cr = cross(a, b, p);
        if (cr < 0) return false;
        if (cr == 0 && onSegment(a, b, p)) return false; // boundary not allowed as inside
    }
    return true; // strictly inside
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a mode for variability
    int mode = rnd.next(0, 2); // 0,1,2

    // Generate a random strictly convex polygon P
    vector<Pt> P;
    int coordRange;
    int rawMinN, rawMaxN;
    if (mode == 0) {
        coordRange = 7;
        rawMinN = 4;
        rawMaxN = 7;
    } else if (mode == 1) {
        coordRange = 12;
        rawMinN = 6;
        rawMaxN = 12;
    } else {
        coordRange = 9;
        rawMinN = 4;
        rawMaxN = 9;
    }

    while (true) {
        int rawN = rnd.next(rawMinN, rawMaxN);
        set<pair<int, int>> used;
        vector<Pt> pts;
        while ((int)pts.size() < rawN) {
            int x = rnd.next(-coordRange, coordRange);
            int y = rnd.next(-coordRange, coordRange);
            pair<int, int> key = {x, y};
            if (used.count(key)) continue;
            used.insert(key);
            pts.push_back(Pt{ x, y });
        }
        vector<Pt> hull = convexHull(pts);
        if ((int)hull.size() >= 3) {
            P = hull;
            break;
        }
    }
    int N = (int)P.size();

    // Generate Q points (not on boundary, distinct, some inside, some outside)
    int M;
    if (mode == 0) M = rnd.next(3, 6);
    else if (mode == 1) M = rnd.next(5, 12);
    else M = rnd.next(4, 10);

    // Bounding box of polygon
    long long minx = P[0].x, maxx = P[0].x, miny = P[0].y, maxy = P[0].y;
    for (const auto& pt : P) {
        minx = min(minx, pt.x);
        maxx = max(maxx, pt.x);
        miny = min(miny, pt.y);
        maxy = max(maxy, pt.y);
    }
    long long spanX = maxx - minx;
    long long spanY = maxy - miny;
    long long margin = max(spanX, spanY) + 3;
    long long bigMin = min(minx, miny) - margin;
    long long bigMax = max(maxx, maxy) + margin;

    set<pair<long long, long long>> usedAll;
    for (const auto& pt : P) usedAll.insert({pt.x, pt.y});

    vector<Pt> Q;
    int wantInside = 1, wantOutside = 0;
    if (M >= 2) {
        wantInside = rnd.next(1, M - 1);
        wantOutside = M - wantInside;
    } else {
        wantInside = 1;
        wantOutside = 0;
    }

    // Generate inside points
    int attempts = 0;
    int insideCount = 0;
    while (insideCount < wantInside && attempts < 10000) {
        long long x = rnd.next((int)minx, (int)maxx);
        long long y = rnd.next((int)miny, (int)maxy);
        pair<long long, long long> key = {x, y};
        if (usedAll.count(key)) {
            attempts++;
            continue;
        }
        Pt p{ x, y };
        if (isOnBoundary(P, p)) {
            attempts++;
            continue;
        }
        if (isInsideStrict(P, p)) {
            Q.push_back(p);
            usedAll.insert(key);
            insideCount++;
        }
        attempts++;
    }

    // Generate outside points
    attempts = 0;
    int outsideCount = 0;
    while (outsideCount < wantOutside && attempts < 20000) {
        long long x = rnd.next((int)bigMin, (int)bigMax);
        long long y = rnd.next((int)bigMin, (int)bigMax);
        pair<long long, long long> key = {x, y};
        if (usedAll.count(key)) {
            attempts++;
            continue;
        }
        Pt p{ x, y };
        if (isOnBoundary(P, p)) {
            attempts++;
            continue;
        }
        if (isInsideStrict(P, p)) {
            attempts++;
            continue; // we want outside
        }
        Q.push_back(p);
        usedAll.insert(key);
        outsideCount++;
        attempts++;
    }

    // If not enough points yet, fill remaining with arbitrary (inside or outside) but not on boundary
    attempts = 0;
    while ((int)Q.size() < M && attempts < 30000) {
        long long x = rnd.next((int)bigMin, (int)bigMax);
        long long y = rnd.next((int)bigMin, (int)bigMax);
        pair<long long, long long> key = {x, y};
        if (usedAll.count(key)) {
            attempts++;
            continue;
        }
        Pt p{ x, y };
        if (isOnBoundary(P, p)) {
            attempts++;
            continue;
        }
        Q.push_back(p);
        usedAll.insert(key);
        attempts++;
    }

    // Ensure we have exactly M points (should hold, but just in case)
    while ((int)Q.size() > M) Q.pop_back();

    // Generate queries
    int K;
    int Kmin = 3;
    int Kmax;
    if (mode == 1) Kmax = min(25, M * (M - 1));
    else Kmax = min(12, M * (M - 1));
    if (Kmax < Kmin) Kmax = Kmin;
    K = rnd.next(Kmin, Kmax);

    vector<pair<int, int>> queries;
    // Some structured neighbor queries if possible
    if (M >= 2) {
        for (int i = 0; i < M && (int)queries.size() < K; i++) {
            int a = i + 1;
            int b = (i + 1) % M + 1;
            if (a != b) queries.push_back({a, b});
        }
        // Some reversed
        for (int i = 0; i < (int)queries.size() && (int)queries.size() < K; i++) {
            int a = queries[i].second;
            int b = queries[i].first;
            if (a != b) queries.push_back({a, b});
        }
    }
    // Fill remaining randomly
    while ((int)queries.size() < K) {
        int a = rnd.next(1, M);
        int b = rnd.next(1, M - 1);
        if (b >= a) b++;
        queries.push_back({a, b});
    }

    // Output
    println(N, M, K);
    for (const auto& pt : P) {
        println(pt.x, pt.y);
    }
    for (const auto& pt : Q) {
        println(pt.x, pt.y);
    }
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}
