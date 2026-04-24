#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first set size
    int n1 = inf.readInt(1, 1000, "n1");
    inf.readEoln();

    // Read P1 points
    vector<pair<int,int>> pts;
    pts.reserve(n1);
    for (int i = 0; i < n1; i++) {
        int x = inf.readInt(-1000000000, 1000000000, "x1");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y1");
        inf.readEoln();
        pts.emplace_back(x, y);
    }

    // Read second set size
    int n2 = inf.readInt(1, 1000, "n2");
    inf.readEoln();

    // Read P2 points
    pts.reserve(n1 + n2);
    for (int i = 0; i < n2; i++) {
        int x = inf.readInt(-1000000000, 1000000000, "x2");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y2");
        inf.readEoln();
        pts.emplace_back(x, y);
    }

    // Read constants c1, c2
    int c1 = inf.readInt(1, 10000, "c1");
    inf.readSpace();
    int c2 = inf.readInt(1, 10000, "c2");
    inf.readEoln();

    // Check global uniqueness of x and y coordinates
    set<int> xs, ys;
    for (int i = 0; i < (int)pts.size(); i++) {
        int x = pts[i].first;
        int y = pts[i].second;
        bool insertedX = xs.insert(x).second;
        ensuref(insertedX,
                "Duplicate x-coordinate detected at point index %d: x = %d", i, x);
        bool insertedY = ys.insert(y).second;
        ensuref(insertedY,
                "Duplicate y-coordinate detected at point index %d: y = %d", i, y);
    }

    inf.readEof();
    return 0;
}
