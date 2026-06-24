#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-6;

struct Point {
    double x;
    double y;
};

vector<Point> facilities;

double score(const Point& home) {
    double nearest = 1e300;
    double farthest = 0.0;

    for (const Point& facility : facilities) {
        double dx = home.x - facility.x;
        double dy = home.y - facility.y;
        double distance = hypot(dx, dy);
        nearest = min(nearest, distance);
        farthest = max(farthest, distance);
    }

    return (nearest + farthest) / 2.0;
}

Point readPoint(InStream& stream) {
    double x = stream.readDouble(-1e100, 1e100, "H_x");
    double y = stream.readDouble(-1e100, 1e100, "H_y");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after coordinates");
    }
    return {x, y};
}

bool closeEnough(double expected, double actual) {
    return abs(expected - actual) <= EPS || abs(expected - actual) <= abs(expected) * EPS;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    facilities.resize(n);
    for (int i = 0; i < n; ++i) {
        facilities[i].x = inf.readInt();
        facilities[i].y = inf.readInt();
    }

    Point juryPoint = readPoint(ans);
    Point participantPoint = readPoint(ouf);

    double juryScore = score(juryPoint);
    double participantScore = score(participantPoint);

    if (closeEnough(juryScore, participantScore)) {
        quitf(_ok, "answer %.12f is within tolerance of jury %.12f", participantScore, juryScore);
    }
    if (participantScore < juryScore) {
        quitf(_fail,
              "participant found a better answer: participant %.12f, jury %.12f",
              participantScore,
              juryScore);
    }

    quitf(_wa,
          "answer %.12f is not within tolerance of jury %.12f",
          participantScore,
          juryScore);
}
