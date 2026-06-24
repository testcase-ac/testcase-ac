#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readProbability(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "probability must be finite");
    }
    if (value < 0.0 || value > 1.0) {
        stream.quitf(_wa, "probability %.12f is outside [0, 1]", value);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after probability");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readProbability(ans);
    double participant = readProbability(ouf);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa, "expected %.12f, found %.12f, error %.12f",
              jury, participant, doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
