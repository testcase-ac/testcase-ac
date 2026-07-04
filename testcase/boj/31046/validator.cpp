#include "testlib.h"

#include <vector>

using namespace std;

struct Circle {
    int x;
    int y;
    int r;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    vector<Circle> circles;
    circles.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000, 1000, "X");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "Y");
        inf.readSpace();
        int r = inf.readInt(1, 100, "R");
        inf.readEoln();

        for (int j = 0; j < i; ++j) {
            long long dx = x - circles[j].x;
            long long dy = y - circles[j].y;
            long long radiusSum = r + circles[j].r;
            ensuref(dx * dx + dy * dy >= radiusSum * radiusSum,
                    "circles %d and %d overlap: centers (%d, %d), (%d, %d), radii %d, %d",
                    j + 1, i + 1, circles[j].x, circles[j].y, x, y, circles[j].r, r);
        }

        circles.push_back({x, y, r});
    }

    inf.readEof();
}
