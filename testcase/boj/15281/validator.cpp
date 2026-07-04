#include "testlib.h"

#include <array>

using namespace std;

long long squaredDistance(const array<int, 2>& a, const array<int, 2>& b) {
    long long dx = a[0] - b[0];
    long long dy = a[1] - b[1];
    return dx * dx + dy * dy;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<array<int, 2>, 3> p;
    for (int i = 0; i < 3; ++i) {
        p[i][0] = inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        p[i][1] = inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();
    }

    int xv = inf.readInt(-1000, 1000, "x_v");
    inf.readSpace();
    int yv = inf.readInt(-1000, 1000, "y_v");
    inf.readSpace();
    int r = inf.readInt(1, 50, "r");
    inf.readEoln();

    // CHECK: The statement describes (x_v, y_v) as a direction vector, so it cannot be zero.
    ensuref(xv != 0 || yv != 0, "direction vector must be nonzero");

    long long touchDistanceSquared = 4LL * r * r;
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            ensuref(squaredDistance(p[i], p[j]) > touchDistanceSquared,
                    "particles %d and %d touch or overlap initially", i + 1, j + 1);
        }
    }

    long long secondaryDistanceSquared = 16LL * r * r;
    ensuref(squaredDistance(p[1], p[2]) > secondaryDistanceSquared,
            "distance between particles 2 and 3 must be greater than 4r");

    inf.readEof();
}
