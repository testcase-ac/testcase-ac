#include "testlib.h"
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, x_L, y_L, x_B, y_B
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int xL = inf.readInt(0, 1000000000, "x_L");
    inf.readSpace();
    int yL = inf.readInt(0, 1000000000, "y_L");
    inf.readSpace();
    int xB = inf.readInt(0, 1000000000, "x_B");
    inf.readSpace();
    int yB = inf.readInt(0, 1000000000, "y_B");
    inf.readEoln();

    // Laser and barn must be at distinct locations
    ensuref(!(xL == xB && yL == yB),
            "Laser and barn locations must be distinct: both at (%d, %d)", xL, yL);

    // Read fence posts, ensure distinctness and bounds
    unordered_set<unsigned long long> seen;
    seen.reserve(N * 2);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();

        // Distinct from laser
        ensuref(!(x == xL && y == yL),
                "Fence post %d at (%d, %d) coincides with the laser location", i, x, y);
        // Distinct from barn
        ensuref(!(x == xB && y == yB),
                "Fence post %d at (%d, %d) coincides with the barn location", i, x, y);

        // Distinct among fence posts
        unsigned long long key = ( (unsigned long long)x << 32 ) | (unsigned long long)y;
        ensuref(!seen.count(key),
                "Duplicate fence post detected at index %d: (%d, %d)", i, x, y);
        seen.insert(key);
    }

    inf.readEof();
    return 0;
}
