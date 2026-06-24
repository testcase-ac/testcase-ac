#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;
const double MIN_PROBABILITY = 0.0;
const double MAX_PROBABILITY = 1.0;

double readProbability(InStream& stream, TResult invalidVerdict, const char* owner) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidVerdict, "%s answer is not finite", owner);
    }
    if (value < MIN_PROBABILITY || value > MAX_PROBABILITY) {
        stream.quitf(invalidVerdict, "%s answer %.17g is outside [0, 1]", owner, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s answer", owner);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readProbability(ans, _fail, "jury");
    double participant = readProbability(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
