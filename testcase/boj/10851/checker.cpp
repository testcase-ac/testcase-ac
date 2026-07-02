#include "testlib.h"

#include <cmath>
using namespace std;

const long double EPS = 1e-4L;

struct Answer {
    long double s;
};

Answer readAnswer(InStream& stream, bool juryOutput) {
    long double s = stream.readDouble();
    stream.readEoln();
    stream.readEof();
    if (!isfinite((double)s)) {
        stream.quitf(_wa, "s must be finite");
    }
    if (juryOutput && (s < 2.0L || s > 1000.0L)) {
        stream.quitf(_wa, "jury s %.10Lf is outside [2, 1000]", s);
    }
    return {s};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, true);
    Answer participant = readAnswer(ouf, false);

    long double error = fabsl(participant.s - jury.s);
    if (error <= EPS) {
        quitf(_ok, "s=%.10Lf is within absolute error %.10Lf", participant.s, error);
    }

    quitf(_wa,
          "expected %.10Lf, found %.10Lf, absolute error %.10Lf exceeds %.10Lf",
          jury.s,
          participant.s,
          error,
          EPS);
}
