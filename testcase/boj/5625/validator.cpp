#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int max_coord = 999999;

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(0, max_coord, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, max_coord, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, max_coord, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, max_coord, "y2");
        inf.readSpace();
        int x3 = inf.readInt(0, max_coord, "x3");
        inf.readSpace();
        int y3 = inf.readInt(0, max_coord, "y3");
        inf.readEoln();

        long long area2 = 1LL * (x2 - x1) * (y3 - y1) -
                          1LL * (y2 - y1) * (x3 - x1);
        ensuref(area2 != 0, "triangle %d vertices are collinear", i);
    }

    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        string axis = inf.readToken("[xy]", "axis");
        inf.readSpace();
        inf.readToken("[=]", "equals");
        inf.readSpace();
        inf.readInt(0, max_coord, "c");
        inf.readEoln();
    }

    inf.readEof();
}
