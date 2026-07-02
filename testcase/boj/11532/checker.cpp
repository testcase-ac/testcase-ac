#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-3;

struct Answer {
    int droplets;
    double time;
};

Answer readAnswer(InStream& stream, int n) {
    int droplets = stream.readInt(1, n, "k");
    double time = stream.readDouble(0.0, 1e100, "t");

    if (!isfinite(time)) {
        stream.quitf(_wa, "time must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    return {droplets, time};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(2, 100, "N");

    Answer jury = readAnswer(ans, n);
    Answer participant = readAnswer(ouf, n);

    if (participant.droplets != jury.droplets) {
        quitf(_wa,
              "expected k=%d, found k=%d",
              jury.droplets,
              participant.droplets);
    }

    if (!doubleCompare(jury.time, participant.time, EPS)) {
        quitf(_wa,
              "expected t=%.17g, found t=%.17g, error=%.17g",
              jury.time,
              participant.time,
              doubleDelta(jury.time, participant.time));
    }

    quitf(_ok, "k=%d and t=%.17g are accepted", participant.droplets, participant.time);
}
