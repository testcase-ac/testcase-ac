#include "testlib.h"

#include <cmath>
#include <vector>
using namespace std;

static const double EPS = 5e-4 + 1e-12;

struct Point {
    double x;
    double y;
};

vector<Point> readOutput(InStream& stream, int testCases) {
    vector<Point> result(testCases);
    for (int tc = 1; tc <= testCases; ++tc) {
        result[tc - 1].x = stream.readDouble(-1e100, 1e100, format("x[%d]", tc));
        result[tc - 1].y = stream.readDouble(-1e100, 1e100, format("y[%d]", tc));
    }
    if (!stream.seekEof()) {
        stream.quitf((&stream == &ans) ? _fail : _wa, "extra output after %d case(s)", testCases);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCases = inf.readInt();
    vector<Point> jury = readOutput(ans, testCases);
    vector<Point> participant = readOutput(ouf, testCases);

    for (int tc = 1; tc <= testCases; ++tc) {
        const Point& expected = jury[tc - 1];
        const Point& found = participant[tc - 1];
        double dx = fabs(expected.x - found.x);
        double dy = fabs(expected.y - found.y);

        if (dx > EPS || dy > EPS) {
            quitf(_wa,
                  "case %d differs: expected %.10f %.10f, found %.10f %.10f, errors %.10f %.10f",
                  tc,
                  expected.x,
                  expected.y,
                  found.x,
                  found.y,
                  dx,
                  dy);
        }
    }

    quitf(_ok, "all %d case(s) are within %.4f absolute error", testCases, EPS);
}
