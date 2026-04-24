#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(5, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Generate rectangle corners with xmin < xmax and ymin < ymax
        int xa = rnd.next(-10, 10);
        int xb = rnd.next(-10, 10);
        while (xa == xb) xb = rnd.next(-10, 10);
        int xmin = min(xa, xb), xmax = max(xa, xb);

        int ya = rnd.next(-10, 10);
        int yb = rnd.next(-10, 10);
        while (ya == yb) yb = rnd.next(-10, 10);
        int ymin = min(ya, yb), ymax = max(ya, yb);

        // Output the rectangle
        println(xmin, ymin, xmax, ymax);

        // Decide type of intersection to force 0,1,2 or infinite intersections
        // Only allow type 2 (two intersections) if both width and height >= 2
        vector<int> types = {0, 1, 3};
        if (xmax - xmin >= 2 && ymax - ymin >= 2) {
            types.push_back(2);
        }
        int type = rnd.any(types);

        int x1, y1, x2, y2;
        // Generate segment endpoints, ensure they differ
        do {
            if (type == 0) {
                // No intersection: segment lies entirely in one outside half-plane
                int region = rnd.next(0, 3);
                switch (region) {
                    case 0: // above
                        y1 = rnd.next(ymax + 1, ymax + rnd.next(1, 5));
                        y2 = rnd.next(ymax + 1, ymax + rnd.next(1, 5));
                        x1 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        break;
                    case 1: // below
                        y1 = rnd.next(ymin - rnd.next(1, 5), ymin - 1);
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymin - 1);
                        x1 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        break;
                    case 2: // left
                        x1 = rnd.next(xmin - rnd.next(1, 5), xmin - 1);
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmin - 1);
                        y1 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        break;
                    default: // right
                        x1 = rnd.next(xmax + 1, xmax + rnd.next(1, 5));
                        x2 = rnd.next(xmax + 1, xmax + rnd.next(1, 5));
                        y1 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        break;
                }
            }
            else if (type == 1) {
                // Exactly one intersection: one endpoint on boundary, the other strictly outside
                int side = rnd.next(0, 3);
                switch (side) {
                    case 0: // bottom
                        y1 = ymin;
                        x1 = rnd.next(xmin, xmax);
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymin - 1);
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        break;
                    case 1: // top
                        y1 = ymax;
                        x1 = rnd.next(xmin, xmax);
                        y2 = rnd.next(ymax + 1, ymax + rnd.next(1, 5));
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmax + rnd.next(1, 5));
                        break;
                    case 2: // left
                        x1 = xmin;
                        y1 = rnd.next(ymin, ymax);
                        x2 = rnd.next(xmin - rnd.next(1, 5), xmin - 1);
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        break;
                    default: // right
                        x1 = xmax;
                        y1 = rnd.next(ymin, ymax);
                        x2 = rnd.next(xmax + 1, xmax + rnd.next(1, 5));
                        y2 = rnd.next(ymin - rnd.next(1, 5), ymax + rnd.next(1, 5));
                        break;
                }
            }
            else if (type == 2) {
                // Exactly two intersections: endpoints on two different sides (interior points)
                vector<int> sides = {0, 1, 2, 3};
                shuffle(sides.begin(), sides.end());
                int sA = sides[0], sB = sides[1];
                auto onSide = [&](int s, int &x, int &y) {
                    if (s == 0) { // bottom
                        y = ymin;
                        x = rnd.next(xmin + 1, xmax - 1);
                    } else if (s == 1) { // top
                        y = ymax;
                        x = rnd.next(xmin + 1, xmax - 1);
                    } else if (s == 2) { // left
                        x = xmin;
                        y = rnd.next(ymin + 1, ymax - 1);
                    } else { // right
                        x = xmax;
                        y = rnd.next(ymin + 1, ymax - 1);
                    }
                };
                onSide(sA, x1, y1);
                onSide(sB, x2, y2);
            }
            else {
                // Infinite intersections: segment colinear with one boundary side
                int side = rnd.next(0, 3);
                if (side == 0 || side == 1) {
                    int y = (side == 0 ? ymin : ymax);
                    int a = rnd.next(xmin, xmax - 1);
                    int b = rnd.next(a + 1, xmax);
                    x1 = a; y1 = y;
                    x2 = b; y2 = y;
                } else {
                    int x = (side == 2 ? xmin : xmax);
                    int a = rnd.next(ymin, ymax - 1);
                    int b = rnd.next(a + 1, ymax);
                    x1 = x; y1 = a;
                    x2 = x; y2 = b;
                }
            }
            // Ensure non-zero length
        } while (x1 == x2 && y1 == y2);

        // Output the segment
        println(x1, y1, x2, y2);
    }

    return 0;
}
