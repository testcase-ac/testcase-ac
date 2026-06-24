#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readProbability(InStream& stream, TResult invalidOutcome, const char* who) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidOutcome, "%s answer is not finite", who);
    }
    if (value < -EPS || value > 1.0 + EPS) {
        stream.quitf(invalidOutcome, "%s probability %.12f is outside [0, 1]", who, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidOutcome, "extra output after %s answer", who);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readProbability(ans, _fail, "jury");
    double participant = readProbability(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
