#include "testlib.h"

#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

double readAnswer(InStream& stream, TResult invalidResult, int lastMod) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "answer is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after answer");
    }

    double low = -EPS;
    double high = max(0, lastMod - 1) + EPS;
    if (value < low || value > high) {
        stream.quitf(
            invalidResult,
            "answer %.17g is outside valid expectation range [0, %d]",
            value,
            max(0, lastMod - 1));
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int lastMod = 1;
    for (int i = 0; i < n; ++i) {
        lastMod = inf.readInt();
    }

    double jury = readAnswer(ans, _fail, lastMod);
    double participant = readAnswer(ouf, _wa, lastMod);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(
            _wa,
            "expected %.17g, found %.17g, error %.17g",
            jury,
            participant,
            doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
