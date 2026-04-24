#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

// Check if point (x,y) is on the segment p->q (inclusive)
bool onSegment(pair<int,int> p, pair<int,int> q, int x, int y) {
    if (p.first == q.first) {
        // vertical
        if (x != p.first) return false;
        return y >= min(p.second, q.second) && y <= max(p.second, q.second);
    } else if (p.second == q.second) {
        // horizontal
        if (y != p.second) return false;
        return x >= min(p.first, q.first) && x <= max(p.first, q.first);
    }
    return false;
}

// Ray-casting point-in-polygon
bool isInside(const vector<pair<int,int>>& poly, int x, int y) {
    bool inside = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        int xi = poly[i].first, yi = poly[i].second;
        int xj = poly[j].first, yj = poly[j].second;
        // check if point is on boundary edge
        if (onSegment(poly[i], poly[j], x, y)) return false;
        bool intersect = ((yi > y) != (yj > y)) &&
                         (double)x < (double)(xj - xi) * (y - yi) / (double)(yj - yi) + xi;
        if (intersect)
            inside = !inside;
    }
    return inside;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose rectangle or L-shape
    int shapeType = rnd.next(0, 1);
    vector<pair<int,int>> corners;
    if (shapeType == 0) {
        // Rectangle
        int w = rnd.next(5, 20);
        int h = rnd.next(5, 20);
        corners = {{0,0},{w,0},{w,h},{0,h}};
    } else {
        // L-shape
        int w1 = rnd.next(3, 10);
        int w2 = rnd.next(3, 10);
        int h1 = rnd.next(3, 10);
        int h2 = rnd.next(3, 10);
        // CCW
        corners = {
            {0, 0},
            {w1 + w2, 0},
            {w1 + w2, h1},
            {w1, h1},
            {w1, h1 + h2},
            {0, h1 + h2}
        };
    }
    int n = corners.size();

    // Build all integer wall points
    set<pair<int,int>> wallSet;
    for (int i = 0; i < n; i++) {
        auto p = corners[i];
        auto q = corners[(i+1)%n];
        if (p.first == q.first) {
            // vertical
            int x = p.first;
            int y1 = min(p.second, q.second);
            int y2 = max(p.second, q.second);
            for (int y = y1; y <= y2; y++)
                wallSet.insert({x,y});
        } else {
            // horizontal
            int y = p.second;
            int x1 = min(p.first, q.first);
            int x2 = max(p.first, q.first);
            for (int x = x1; x <= x2; x++)
                wallSet.insert({x,y});
        }
    }
    vector<pair<int,int>> wallPoints(wallSet.begin(), wallSet.end());

    // Hyper-parameters for k, holes, mice
    int k = rnd.next(1, 5);
    int maxH = min<int>(20, wallPoints.size());
    int h_count = rnd.next(1, maxH);

    // Compute bounding box for interior search
    int minX = corners[0].first, maxX = corners[0].first;
    int minY = corners[0].second, maxY = corners[0].second;
    for (auto &p : corners) {
        minX = min(minX, p.first);
        maxX = max(maxX, p.first);
        minY = min(minY, p.second);
        maxY = max(maxY, p.second);
    }

    // Build interior integer points
    vector<pair<int,int>> interior;
    for (int x = minX+1; x < maxX; x++) {
        for (int y = minY+1; y < maxY; y++) {
            // skip boundary
            bool onB = false;
            for (int i = 0; i < n; i++) {
                if (onSegment(corners[i], corners[(i+1)%n], x, y)) {
                    onB = true; break;
                }
            }
            if (onB) continue;
            if (isInside(corners, x, y))
                interior.emplace_back(x,y);
        }
    }
    // ensure at least one interior
    if (interior.empty()) {
        // fallback: pick center of rectangle
        int cx = (minX + maxX) / 2;
        int cy = (minY + maxY) / 2;
        interior.push_back({cx, cy});
    }

    int m_max = min<int>(k * h_count, interior.size());
    int m_count = rnd.next(1, m_max);

    // Pick holes and mice
    shuffle(wallPoints.begin(), wallPoints.end());
    vector<pair<int,int>> holes(wallPoints.begin(), wallPoints.begin() + h_count);
    shuffle(interior.begin(), interior.end());
    vector<pair<int,int>> mice(interior.begin(), interior.begin() + m_count);

    // Output
    println(n, k, h_count, m_count);
    for (auto &p : corners)
        println(p.first, p.second);
    for (auto &p : holes)
        println(p.first, p.second);
    for (auto &p : mice)
        println(p.first, p.second);
    return 0;
}
