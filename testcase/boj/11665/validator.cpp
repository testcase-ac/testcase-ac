#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Store intersection bounds
    int inter_x1 = 1, inter_y1 = 1, inter_z1 = 1;
    int inter_x2 = 1000, inter_y2 = 1000, inter_z2 = 1000;

    for (int i = 0; i < N; ++i) {
        int x1 = inf.readInt(1, 1000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 1000, "y1");
        inf.readSpace();
        int z1 = inf.readInt(1, 1000, "z1");
        inf.readSpace();
        int x2 = inf.readInt(1, 1000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 1000, "y2");
        inf.readSpace();
        int z2 = inf.readInt(1, 1000, "z2");
        inf.readEoln();

        ensuref(x1 < x2, "On box %d: x1 (%d) must be less than x2 (%d)", i+1, x1, x2);
        ensuref(y1 < y2, "On box %d: y1 (%d) must be less than y2 (%d)", i+1, y1, y2);
        ensuref(z1 < z2, "On box %d: z1 (%d) must be less than z2 (%d)", i+1, z1, z2);

        // Update intersection
        if (x1 > inter_x1) inter_x1 = x1;
        if (y1 > inter_y1) inter_y1 = y1;
        if (z1 > inter_z1) inter_z1 = z1;
        if (x2 < inter_x2) inter_x2 = x2;
        if (y2 < inter_y2) inter_y2 = y2;
        if (z2 < inter_z2) inter_z2 = z2;
    }

    // No further global property to check, since the problem does not guarantee non-empty intersection.
    // But we can check that the intersection volume is in [0, 999^3]
    long long dx = max(0, inter_x2 - inter_x1);
    long long dy = max(0, inter_y2 - inter_y1);
    long long dz = max(0, inter_z2 - inter_z1);
    long long volume = dx * dy * dz;
    ensuref(volume >= 0 && volume <= 999LL * 999 * 999, "Intersection volume out of expected bounds: %lld", volume);

    inf.readEof();
}
