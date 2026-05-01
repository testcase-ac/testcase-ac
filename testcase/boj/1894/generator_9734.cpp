#include "testlib.h"
#include <cstdio>
#include <vector>
using namespace std;

struct PointLL {
    long long x, y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long BASE = 2000000;   // up to 2000.000
    const long long VECTOR = 3000000; // up to 3000.000

    int numCases = rnd.next(1, 5);

    for (int cs = 0; cs < numCases; ++cs) {
        // Choose pattern for variety
        int pattern = rnd.next(0, 2);

        long long x0 = rnd.next(-BASE, BASE);
        long long y0 = rnd.next(-BASE, BASE);

        long long ux = 0, uy = 0, vx = 0, vy = 0;

        if (pattern == 0) {
            // Axis-aligned rectangle
            long long dx = rnd.next(1LL, VECTOR);
            long long dy = rnd.next(1LL, VECTOR);
            if (rnd.next(0, 1)) dx = -dx;
            if (rnd.next(0, 1)) dy = -dy;
            ux = dx; uy = 0;
            vx = 0;  vy = dy;
        } else if (pattern == 1) {
            // Slender, almost collinear edges
            long long k = rnd.next(1LL, VECTOR);
            if (rnd.next(0, 1)) k = -k;
            ux = k; uy = 0;
            long long smallY = rnd.next(1LL, VECTOR / 1000 + 1); // small offset
            if (rnd.next(0, 1)) smallY = -smallY;
            vx = k; vy = smallY; // not collinear with ux
        } else {
            // General parallelogram
            do {
                ux = rnd.next(-VECTOR, VECTOR);
                uy = rnd.next(-VECTOR, VECTOR);
            } while (ux == 0 && uy == 0);
            do {
                vx = rnd.next(-VECTOR, VECTOR);
                vy = rnd.next(-VECTOR, VECTOR);
            } while ((vx == 0 && vy == 0) || (ux * vy - uy * vx == 0));
        }

        // Build parallelogram vertices A,B,C,D
        PointLL v[4];
        v[0] = {x0, y0};                     // A
        v[1] = {x0 + ux, y0 + uy};           // B = A + u
        v[2] = {x0 + ux + vx, y0 + uy + vy}; // C = A + u + v
        v[3] = {x0 + vx, y0 + vy};           // D = A + v

        // Choose shared vertex and two adjacent sides
        int shared = rnd.next(0, 3);
        int left = (shared + 3) % 4;
        int right = (shared + 1) % 4;

        PointLL e1a, e1b, e2a, e2b;

        bool rev1 = rnd.next(0, 1);
        bool rev2 = rnd.next(0, 1);

        if (!rev1) { e1a = v[shared]; e1b = v[left]; }
        else        { e1a = v[left];  e1b = v[shared]; }

        if (!rev2) { e2a = v[shared]; e2b = v[right]; }
        else        { e2a = v[right]; e2b = v[shared]; }

        double x1 = e1a.x / 1000.0;
        double y1 = e1a.y / 1000.0;
        double x2 = e1b.x / 1000.0;
        double y2 = e1b.y / 1000.0;
        double x3 = e2a.x / 1000.0;
        double y3 = e2a.y / 1000.0;
        double x4 = e2b.x / 1000.0;
        double y4 = e2b.y / 1000.0;

        printf("%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
               x1, y1, x2, y2, x3, y3, x4, y4);
    }

    return 0;
}
