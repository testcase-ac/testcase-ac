#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidResult, const char* name) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "%s must be finite", name);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after %s", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury answer");
    double participant = readAnswer(ouf, _wa, "participant answer");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g exceeds %.1e",
              jury,
              participant,
              doubleDelta(jury, participant),
              EPS);
    }

    quitf(_ok, "answer %.17g is within tolerance %.1e", participant, EPS);
}
