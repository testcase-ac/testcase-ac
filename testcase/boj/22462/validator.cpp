#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int sx = inf.readInt(-100, 100, "sx");
    inf.readSpace();
    int sy = inf.readInt(-100, 100, "sy");
    inf.readSpace();
    int gx = inf.readInt(-100, 100, "gx");
    inf.readSpace();
    int gy = inf.readInt(-100, 100, "gy");
    inf.readEoln();

    int n = inf.readInt(0, 1000, "n");
    inf.readEoln();

    set<pair<int, int>> furniture;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-100, 100, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100, 100, "y_i");
        inf.readEoln();

        ensuref(furniture.insert({x, y}).second,
                "duplicate furniture coordinate at index %d: (%d, %d)", i, x, y);
    }

    int lx = inf.readInt(1, 100, "lx");
    inf.readSpace();
    int ly = inf.readInt(1, 100, "ly");
    inf.readEoln();

    ensuref(-lx <= sx && sx <= lx, "start x coordinate %d is outside [-lx, lx]", sx);
    ensuref(-ly <= sy && sy <= ly, "start y coordinate %d is outside [-ly, ly]", sy);
    ensuref(-lx <= gx && gx <= lx, "goal x coordinate %d is outside [-lx, lx]", gx);
    ensuref(-ly <= gy && gy <= ly, "goal y coordinate %d is outside [-ly, ly]", gy);
    ensuref(sx != gx || sy != gy, "start and goal coordinates must differ");

    ensuref(!furniture.count({sx, sy}), "furniture must not be on the start coordinate");
    ensuref(!furniture.count({gx, gy}), "furniture must not be on the goal coordinate");
    for (auto [x, y] : furniture) {
        ensuref(-lx <= x && x <= lx, "furniture x coordinate %d is outside [-lx, lx]", x);
        ensuref(-ly <= y && y <= ly, "furniture y coordinate %d is outside [-ly, ly]", y);
    }

    inf.readEof();
}
