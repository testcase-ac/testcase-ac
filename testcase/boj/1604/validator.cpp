#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>
#include <tuple>
using namespace std;

// Helper function to check if a point is strictly outside the square
bool is_outside_square(int x, int y) {
    // Square is from (-10, -10) to (10, 10), sides included
    // "정사각형 밖에 위치한" means strictly outside, so not on the border
    return x < -10 || x > 10 || y < -10 || y > 10;
}

// Helper function to check if two segments are collinear
bool are_collinear(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    // Two segments (x1,y1)-(x2,y2) and (x3,y3)-(x4,y4) are collinear if the direction vectors are scalar multiples
    // That is, (x2-x1, y2-y1) x (x4-x3, y4-y3) == 0 and (x3-x1, y3-y1) x (x2-x1, y2-y2) == 0
    int dx1 = x2 - x1, dy1 = y2 - y1;
    int dx2 = x4 - x3, dy2 = y4 - y3;
    // Cross product of direction vectors
    long long cross = 1LL * dx1 * dy2 - 1LL * dy1 * dx2;
    if (cross != 0) return false;
    // Now check if (x3,y3)-(x1,y1) is also collinear with direction vector
    long long cross2 = 1LL * (x3 - x1) * dy1 - 1LL * (y3 - y1) * dx1;
    return cross2 == 0;
}

// Helper function to check if three lines meet at a single point
// Each line is given by two points (x1,y1)-(x2,y2), etc.
bool three_lines_meet_at_point(
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4,
    int x5, int y5, int x6, int y6
) {
    // Find intersection of first two lines
    // Line 1: (x1,y1)-(x2,y2)
    // Line 2: (x3,y3)-(x4,y4)
    // Line 3: (x5,y5)-(x6,y6)
    // If all three lines meet at a single point, then intersection point of 1&2 lies on line 3

    // Represent lines as a1x + b1y = c1
    auto get_line = [](int x1, int y1, int x2, int y2) {
        int a = y2 - y1;
        int b = x1 - x2;
        int c = a * x1 + b * y1;
        return tuple<int,int,int>(a,b,c);
    };
    int a1, b1, c1, a2, b2, c2, a3, b3, c3;
    tie(a1,b1,c1) = get_line(x1,y1,x2,y2);
    tie(a2,b2,c2) = get_line(x3,y3,x4,y4);
    tie(a3,b3,c3) = get_line(x5,y5,x6,y6);

    int det = a1 * b2 - a2 * b1;
    if (det == 0) return false; // parallel, do not intersect

    // Intersection point (ix, iy)
    double ix = (double)(b2 * c1 - b1 * c2) / det;
    double iy = (double)(a1 * c2 - a2 * c1) / det;

    // Check if (ix, iy) lies on line 3
    // a3 * ix + b3 * iy == c3
    double val = a3 * ix + b3 * iy - c3;
    return fabs(val) < 1e-8;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Store all segments for global checks
    struct Segment {
        int x1, y1, x2, y2;
    };
    vector<Segment> segs;

    for (int i = 0; i < N; ++i) {
        int x1 = inf.readInt(-1000, 1000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-1000, 1000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-1000, 1000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-1000, 1000, "y2");
        inf.readEoln();

        ensuref(is_outside_square(x1, y1), "Segment %d endpoint 1 (%d,%d) is not strictly outside the square", i+1, x1, y1);
        ensuref(is_outside_square(x2, y2), "Segment %d endpoint 2 (%d,%d) is not strictly outside the square", i+1, x2, y2);
        ensuref(!(x1 == x2 && y1 == y2), "Segment %d is a point, endpoints are identical (%d,%d)", i+1, x1, y1);

        segs.push_back({x1, y1, x2, y2});
    }

    // Check: No two segments are collinear
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            bool col = are_collinear(
                segs[i].x1, segs[i].y1, segs[i].x2, segs[i].y2,
                segs[j].x1, segs[j].y1, segs[j].x2, segs[j].y2
            );
            ensuref(!col, "Segments %d and %d are collinear", i+1, j+1);
        }
    }

    // Check: No three segments meet at a single point
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            for (int k = j+1; k < N; ++k) {
                bool meet = three_lines_meet_at_point(
                    segs[i].x1, segs[i].y1, segs[i].x2, segs[i].y2,
                    segs[j].x1, segs[j].y1, segs[j].x2, segs[j].y2,
                    segs[k].x1, segs[k].y1, segs[k].x2, segs[k].y2
                );
                ensuref(!meet, "Segments %d, %d, %d have lines meeting at a single point", i+1, j+1, k+1);
            }
        }
    }

    inf.readEof();
}
