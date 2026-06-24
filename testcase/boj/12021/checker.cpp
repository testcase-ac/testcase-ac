#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

struct Point {
    double x;
    double y;
};

Point readPoint(InStream& stream) {
    Point p;
    p.x = stream.readDouble();
    p.y = stream.readDouble();
    return p;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Point jury = readPoint(ans);
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    Point participant = readPoint(ouf);
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    if (!doubleCompare(jury.x, participant.x, EPS)) {
        quitf(_wa,
              "x differs: expected %.17g, found %.17g, error %.17g",
              jury.x,
              participant.x,
              doubleDelta(jury.x, participant.x));
    }

    if (!doubleCompare(jury.y, participant.y, EPS)) {
        quitf(_wa,
              "y differs: expected %.17g, found %.17g, error %.17g",
              jury.y,
              participant.y,
              doubleDelta(jury.y, participant.y));
    }

    quitf(_ok, "coordinates are within tolerance");
}
