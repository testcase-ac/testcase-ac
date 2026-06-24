#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer is not finite");
    }
    if (value < 0.0) {
        stream.quitf(_wa, "answer %.17g is negative", value);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
