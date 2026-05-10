#include "testlib.h"
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;

// Helper: Check if two segments (axis-aligned) intersect at a point (not overlap)
bool segments_intersect(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4
) {
    // First segment: (x1,y1)-(x2,y2)
    // Second: (x3,y3)-(x4,y4)
    // Only vertical-horizontal intersection allowed
    if (x1 == x2 && y3 == y4) {
        // First is vertical, second is horizontal
        // Check if they cross at a single point
        if (min(y1, y2) < y3 && y3 < max(y1, y2) &&
            min(x3, x4) < x1 && x1 < max(x3, x4)) {
            return true;
        }
    }
    if (y1 == y2 && x3 == x4) {
        // First is horizontal, second is vertical
        if (min(x1, x2) < x3 && x3 < max(x1, x2) &&
            min(y3, y4) < y1 && y1 < max(y3, y4)) {
            return true;
        }
    }
    return false;
}

// Helper: Check if two segments (axis-aligned) overlap (not just touch at a point)
bool segments_overlap(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4
) {
    // Both horizontal
    if (y1 == y2 && y3 == y4 && y1 == y3) {
        int l1 = min(x1, x2), r1 = max(x1, x2);
        int l2 = min(x3, x4), r2 = max(x3, x4);
        if (max(l1, l2) < min(r1, r2)) return true;
    }
    // Both vertical
    if (x1 == x2 && x3 == x4 && x1 == x3) {
        int l1 = min(y1, y2), r1 = max(y1, y2);
        int l2 = min(y3, y4), r2 = max(y3, y4);
        if (max(l1, l2) < min(r1, r2)) return true;
    }
    return false;
}

// Helper: Check if two segments (axis-aligned) touch at endpoint
bool segments_touch_at_endpoint(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4
) {
    // They share an endpoint
    if ((x1 == x3 && y1 == y3) || (x1 == x4 && y1 == y4) ||
        (x2 == x3 && y2 == y3) || (x2 == x4 && y2 == y4)) {
        return true;
    }
    return false;
}

// Helper: Check if point is in [min(a,b), max(a,b)]
bool in_range(int x, int a, int b) {
    return min(a,b) <= x && x <= max(a,b);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read start point
    int x0 = inf.readInt(1, 100, "x0");
    inf.readSpace();
    int y0 = inf.readInt(1, 100, "y0");
    inf.readEoln();

    // 2. Read n
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // 3. Read moves
    vector<pair<char, int>> moves;
    for (int i = 0; i < n; ++i) {
        string dir = inf.readToken("[UDRL]", "direction");
        inf.readSpace();
        int dist = inf.readInt(1, 100, "distance");
        inf.readEoln();
        moves.emplace_back(dir[0], dist);
    }

    // 4. Simulate path, collect all points and segments
    vector<pair<int, int>> points;
    points.emplace_back(x0, y0);
    int x = x0, y = y0;
    for (int i = 0; i < n; ++i) {
        char d = moves[i].first;
        int len = moves[i].second;
        int nx = x, ny = y;
        if (d == 'U') ny += len;
        else if (d == 'D') ny -= len;
        else if (d == 'R') nx += len;
        else if (d == 'L') nx -= len;
        else ensuref(false, "Invalid direction at move %d: %c", i+1, d);

        // Check that all coordinates are within [1,100]
        ensuref(1 <= nx && nx <= 100 && 1 <= ny && ny <= 100,
            "Coordinate out of bounds after move %d: (%d, %d)", i+1, nx, ny);

        points.emplace_back(nx, ny);
        x = nx; y = ny;
    }

    // 5. Check that path returns to start
    ensuref(points.back().first == x0 && points.back().second == y0,
        "Path does not return to starting point: ends at (%d, %d), should be (%d, %d)",
        points.back().first, points.back().second, x0, y0);

    // 6. Check that all segments are axis-aligned
    for (int i = 1; i < (int)points.size(); ++i) {
        int x1 = points[i-1].first, y1 = points[i-1].second;
        int x2 = points[i].first, y2 = points[i].second;
        ensuref(x1 == x2 || y1 == y2,
            "Segment %d is not axis-aligned: (%d,%d)-(%d,%d)", i, x1, y1, x2, y2);
        ensuref(!(x1 == x2 && y1 == y2),
            "Zero-length segment at %d: (%d,%d)", i, x1, y1);
    }

    // 7. Check for forbidden intersections and overlaps
    // For each pair of non-adjacent segments, check:
    // - No overlap between two horizontal or two vertical segments
    // - No intersection except at a single point between vertical/horizontal
    // - Touching at endpoints is allowed
    int m = points.size() - 1;
    for (int i = 0; i < m; ++i) {
        int x1 = points[i].first, y1 = points[i].second;
        int x2 = points[i+1].first, y2 = points[i+1].second;
        for (int j = i+1; j < m; ++j) {
            // Adjacent segments (i,j) with |i-j|==1 or (i==0 && j==m-1) are allowed to touch at endpoint
            bool adjacent = (j == i+1) || (i == 0 && j == m-1);
            int x3 = points[j].first, y3 = points[j].second;
            int x4 = points[j+1].first, y4 = points[j+1].second;
            if (segments_overlap(x1,y1,x2,y2,x3,y3,x4,y4)) {
                ensuref(false, "Segments %d and %d overlap: (%d,%d)-(%d,%d) and (%d,%d)-(%d,%d)",
                        i+1, j+1, x1,y1,x2,y2,x3,y3,x4,y4);
            }
            if (segments_intersect(x1,y1,x2,y2,x3,y3,x4,y4)) {
                // Only allowed if intersection is at endpoint (i.e. they share a point)
                // But in our intersection function, it only returns true if they cross at a point not at endpoints
                // So this is always forbidden
                continue; // allowed
            }
            // Check if they cross at a point not at endpoints (forbidden)
            // Already checked above
            // Check if they touch at endpoint (allowed)
            if (segments_touch_at_endpoint(x1,y1,x2,y2,x3,y3,x4,y4)) continue;
            // Otherwise, check if they overlap at a point (forbidden)
            // Already checked above
        }
    }

    // 8. Check that all points are within [1,100]
    for (int i = 0; i < (int)points.size(); ++i) {
        int x = points[i].first, y = points[i].second;
        ensuref(1 <= x && x <= 100 && 1 <= y && y <= 100,
            "Point %d out of bounds: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
