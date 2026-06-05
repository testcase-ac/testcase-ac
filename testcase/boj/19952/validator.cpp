#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int H = inf.readInt(2, 100, "H");
        inf.readSpace();
        int W = inf.readInt(2, 100, "W");
        inf.readSpace();
        int O = inf.readInt(0, H * W, "O");
        inf.readSpace();
        int F = inf.readInt(0, 10000, "F");
        inf.readSpace();
        int Xs = inf.readInt(1, H, "Xs");
        inf.readSpace();
        int Ys = inf.readInt(1, W, "Ys");
        inf.readSpace();
        int Xe = inf.readInt(1, H, "Xe");
        inf.readSpace();
        int Ye = inf.readInt(1, W, "Ye");
        inf.readEoln();

        pair<int, int> start = {Xs, Ys};
        pair<int, int> end = {Xe, Ye};

        set<pair<int, int>> obstacles;
        for (int i = 1; i <= O; ++i) {
            int X = inf.readInt(1, H, "X");
            inf.readSpace();
            int Y = inf.readInt(1, W, "Y");
            inf.readSpace();
            int L = inf.readInt(1, 50, "L");
            inf.readEoln();

            pair<int, int> cell = {X, Y};
            ensuref(cell != start, "obstacle %d is on the start cell (%d, %d)", i, X, Y);
            ensuref(cell != end, "obstacle %d is on the destination cell (%d, %d)", i, X, Y);
            ensuref(obstacles.insert(cell).second, "duplicate obstacle cell at index %d: (%d, %d)", i, X, Y);
        }
    }

    inf.readEof();
}
