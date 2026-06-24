#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidResult) {
    double value = stream.readDouble(0.0, 1e100, "minimum distance");
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "minimum distance must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after minimum distance");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
