#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read starting position
    int xs = inf.readInt(-100000, 100000, "X_s");
    inf.readSpace();
    int ys = inf.readInt(-100000, 100000, "Y_s");
    inf.readEoln();

    // Read maximum time T
    int T = inf.readInt(1, 200, "T");
    inf.readEoln();

    // Read home position
    int xh = inf.readInt(-100000, 100000, "X_h");
    inf.readSpace();
    int yh = inf.readInt(-100000, 100000, "Y_h");
    inf.readEoln();

    // Read number of obstacles
    int N = inf.readInt(0, 100000, "N");
    inf.readEoln();

    // Ensure all coordinates are distinct
    set<pair<int,int>> coords;
    coords.insert({xs, ys});
    ensuref(!(xs == xh && ys == yh),
            "Start and home positions must be distinct but both are (%d, %d)", xs, ys);
    coords.insert({xh, yh});

    // Read obstacle positions
    for (int i = 0; i < N; i++) {
        int xi = inf.readInt(-100000, 100000, "X_i");
        inf.readSpace();
        int yi = inf.readInt(-100000, 100000, "Y_i");
        inf.readEoln();
        pair<int,int> p = {xi, yi};
        ensuref(!coords.count(p),
                "Duplicate coordinate detected at obstacle index %d: (%d, %d)", i, xi, yi);
        coords.insert(p);
    }

    inf.readEof();
    return 0;
}
