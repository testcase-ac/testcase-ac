#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

static const double EPS = 1e-6;

struct Point {
    double first;
    double second;
};

static Point readPoint(InStream& stream, int tc) {
    Point p;
    p.first = stream.readDouble();
    p.second = stream.readDouble();

    if (!isfinite(p.first) || !isfinite(p.second)) {
        stream.quitf(_wa, "answer for test case %d must contain finite real numbers", tc);
    }

    return p;
}

static vector<Point> readAnswer(InStream& stream, int t) {
    vector<Point> result;
    result.reserve(t);

    for (int tc = 1; tc <= t; ++tc) {
        result.push_back(readPoint(stream, tc));
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d coordinate pairs", t);
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        inf.readInt();
        inf.readDouble();
        inf.readDouble();
    }

    vector<Point> jury = readAnswer(ans, t);
    vector<Point> participant = readAnswer(ouf, t);

    for (int tc = 1; tc <= t; ++tc) {
        const Point& expected = jury[tc - 1];
        const Point& found = participant[tc - 1];

        if (!doubleCompare(expected.first, found.first, EPS)) {
            quitf(_wa,
                  "test case %d first value differs: expected %.17g, found %.17g, error %.17g",
                  tc,
                  expected.first,
                  found.first,
                  doubleDelta(expected.first, found.first));
        }

        if (!doubleCompare(expected.second, found.second, EPS)) {
            quitf(_wa,
                  "test case %d second value differs: expected %.17g, found %.17g, error %.17g",
                  tc,
                  expected.second,
                  found.second,
                  doubleDelta(expected.second, found.second));
        }
    }

    quitf(_ok, "%d coordinate pairs are within tolerance", t);
}
