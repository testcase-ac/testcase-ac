#include "testlib.h"

#include <cmath>

using namespace std;

static const double EPS = 1e-6;

double readAnswer(InStream &stream, TResult verdict, const char *owner) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(verdict, "%s answer is not finite", owner);
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s answer", owner);
    }
    return value;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.15f, found %.15f, error %.15f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.15f is within tolerance", participant);
}
