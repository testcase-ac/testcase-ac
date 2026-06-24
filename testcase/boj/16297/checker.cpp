#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidVerdict, const char* label) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidVerdict, "%s answer must be finite", label);
    }
    if (value < 0.0) {
        stream.quitf(invalidVerdict, "%s answer must be non-negative, found %.17g", label, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s answer", label);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa, "expected %.17g, found %.17g, error %.17g",
              jury, participant, doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
