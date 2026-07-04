#include "testlib.h"

#include <cmath>

using namespace std;

struct Point {
    long double x;
    long double y;
    long double z;
};

long double squaredDistance(Point a, Point b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    long double dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

long double segmentDistance(Point a, Point b, Point c) {
    Point ab{b.x - a.x, b.y - a.y, b.z - a.z};
    Point ac{c.x - a.x, c.y - a.y, c.z - a.z};
    long double ab2 = ab.x * ab.x + ab.y * ab.y + ab.z * ab.z;
    long double t = (ac.x * ab.x + ac.y * ab.y + ac.z * ab.z) / ab2;
    if (t < 0.0L) t = 0.0L;
    if (t > 1.0L) t = 1.0L;

    Point closest{a.x + t * ab.x, a.y + t * ab.y, a.z + t * ab.z};
    return sqrtl(squaredDistance(closest, c));
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int ax = inf.readInt(-5000, 5000, "romian_x");
    inf.readSpace();
    int ay = inf.readInt(-5000, 5000, "romian_y");
    inf.readSpace();
    int az = inf.readInt(-5000, 5000, "romian_z");
    inf.readEoln();

    int bx = inf.readInt(-5000, 5000, "julia_x");
    inf.readSpace();
    int by = inf.readInt(-5000, 5000, "julia_y");
    inf.readSpace();
    int bz = inf.readInt(-5000, 5000, "julia_z");
    inf.readEoln();

    ensuref(ax != bx || ay != by || az != bz,
            "Romian and Julia must occupy distinct positions");

    int n = inf.readInt(1, 2000, "n");
    inf.readEoln();

    Point a{(long double)ax, (long double)ay, (long double)az};
    Point b{(long double)bx, (long double)by, (long double)bz};
    const long double eps = 1e-8L;

    for (int i = 0; i < n; ++i) {
        int cx = inf.readInt(-5000, 5000, "center_x");
        inf.readSpace();
        int cy = inf.readInt(-5000, 5000, "center_y");
        inf.readSpace();
        int cz = inf.readInt(-5000, 5000, "center_z");
        inf.readSpace();
        int r = inf.readInt(0, 5000, "radius");
        inf.readEoln();

        Point c{(long double)cx, (long double)cy, (long double)cz};
        long double radius = (long double)r;
        long double da = sqrtl(squaredDistance(a, c));
        long double db = sqrtl(squaredDistance(b, c));

        ensuref(da > radius + eps,
                "Romian is inside or too close to planet %d", i + 1);
        ensuref(db > radius + eps,
                "Julia is inside or too close to planet %d", i + 1);

        long double ds = segmentDistance(a, b, c);
        // CHECK: The statement promises every laser/planet relation is at least
        // 1e-8 away from the tangent boundary; radius 0 planets cannot satisfy
        // the smaller-radius hit promise, so only clear misses are accepted.
        ensuref(ds >= radius + eps || (r > 0 && ds <= radius - eps),
                "planet %d is too close to the laser tangency boundary", i + 1);
    }

    inf.readEof();
}
