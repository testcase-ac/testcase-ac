#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidVerdict, const char* owner) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        quitf(invalidVerdict, "%s answer is not finite", owner);
    }
    if (!stream.seekEof()) {
        quitf(invalidVerdict, "extra output after %s answer", owner);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
