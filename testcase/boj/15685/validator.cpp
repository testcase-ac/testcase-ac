#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of dragon curves
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Direction mapping: 0→, 1↑, 2←, 3↓ (y increases downwards per problem, but validator only cares about bounds)
    static const int dx[4] = {1, 0, -1, 0};
    static const int dy[4] = {0, -1, 0, 1};

    for (int i = 0; i < N; i++) {
        // Read one dragon curve specification
        int x = inf.readInt(0, 100, "x");
        inf.readSpace();
        int y = inf.readInt(0, 100, "y");
        inf.readSpace();
        int d = inf.readInt(0, 3,   "d");
        inf.readSpace();
        int g = inf.readInt(0, 10,  "g");
        inf.readEoln();

        // Simulate the dragon curve to ensure it never goes out of bounds [0,100]×[0,100]
        vector<int> dirs;
        dirs.reserve((1 << 10) + 5);
        dirs.push_back(d);
        // Build up to g-th generation
        for (int gen = 1; gen <= g; gen++) {
            int sz = dirs.size();
            // Append reversed + 1 mod 4
            for (int j = sz - 1; j >= 0; j--) {
                dirs.push_back((dirs[j] + 1) % 4);
            }
        }

        // Traverse the path: record starting point then each step
        int cx = x, cy = y;
        // Starting point is part of the curve; it's in [0,100] by readInt
        for (int s = 0; s < (int)dirs.size(); s++) {
            int nd = dirs[s];
            int nx = cx + dx[nd];
            int ny = cy + dy[nd];
            ensuref(0 <= nx && nx <= 100 && 0 <= ny && ny <= 100,
                    "Curve %d goes out of bounds at segment %d: point (%d,%d)",
                    i+1, s, nx, ny);
            cx = nx;
            cy = ny;
        }
    }

    inf.readEof();
    return 0;
}
