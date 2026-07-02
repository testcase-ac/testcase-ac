#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readProbability(InStream& stream) {
    double value = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after probability");
    }
    if (!isfinite(value)) {
        stream.quitf(_wa, "probability is not finite");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readProbability(ans);
    if (jury < 0.0 || jury > 1.0) {
        quitf(_fail, "jury probability %.17g is outside [0, 1]", jury);
    }

    double participant = readProbability(ouf);
    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "probability %.17g is within tolerance", participant);
}
