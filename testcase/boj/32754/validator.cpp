#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Helper function to compute cross product of two points (vectors)
long long cross(long long x1, long long y1, long long x2, long long y2) {
    return x1 * y2 - y1 * x2;
}

// Helper function to compute dot product of two points (vectors)
long long dot(long long x1, long long y1, long long x2, long long y2) {
    return x1 * x2 + y1 * y2;
}

// Helper function to compute squared distance between two points
long long dist2(long long x1, long long y1, long long x2, long long y2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    return dx * dx + dy * dy;
}

// Check if four points form a non-degenerate rectangle in order
bool is_rectangle(const vector<pair<long long, long long>>& pts) {
    // There must be 4 points
    if (pts.size() != 4) return false;

    // Check that all sides are non-zero length
    for (int i = 0; i < 4; ++i) {
        long long dx = pts[(i+1)%4].first - pts[i].first;
        long long dy = pts[(i+1)%4].second - pts[i].second;
        if (dx == 0 && dy == 0) return false;
    }

    // Check that opposite sides are equal and all angles are right
    long long d01 = dist2(pts[0].first, pts[0].second, pts[1].first, pts[1].second);
    long long d12 = dist2(pts[1].first, pts[1].second, pts[2].first, pts[2].second);
    long long d23 = dist2(pts[2].first, pts[2].second, pts[3].first, pts[3].second);
    long long d30 = dist2(pts[3].first, pts[3].second, pts[0].first, pts[0].second);

    // Opposite sides must be equal
    if (d01 != d23) return false;
    if (d12 != d30) return false;

    // Check right angles using dot product
    for (int i = 0; i < 4; ++i) {
        long long x1 = pts[(i+1)%4].first - pts[i].first;
        long long y1 = pts[(i+1)%4].second - pts[i].second;
        long long x2 = pts[(i+2)%4].first - pts[(i+1)%4].first;
        long long y2 = pts[(i+2)%4].second - pts[(i+1)%4].second;
        if (dot(x1, y1, x2, y2) != 0) return false;
    }

    // Check non-degenerate (area > 0)
    long long area = abs(
        cross(pts[0].first, pts[0].second, pts[1].first, pts[1].second) +
        cross(pts[1].first, pts[1].second, pts[2].first, pts[2].second) +
        cross(pts[2].first, pts[2].second, pts[3].first, pts[3].second) +
        cross(pts[3].first, pts[3].second, pts[0].first, pts[0].second)
    );
    if (area == 0) return false;

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int R = inf.readInt(1, 1000, "R");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        vector<pair<long long, long long>> pts(4);
        for (int j = 0; j < 4; ++j) {
            pts[j].first = inf.readInt(-1000, 1000, format("x_%d%d", i+1, j+1));
            inf.readSpace();
            pts[j].second = inf.readInt(-1000, 1000, format("y_%d%d", i+1, j+1));
            if (j != 3) inf.readSpace();
        }
        inf.readEoln();

        // Check that the four points form a non-degenerate rectangle in order
        ensuref(is_rectangle(pts),
            "The 4 points at device %d do not form a non-degenerate rectangle in order.", i+1);
    }

    inf.readEof();
}
