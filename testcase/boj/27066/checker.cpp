#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;
const double MIN_SCORE = 0.0;
const double MAX_SCORE = 10000.0;

double readAnswer(InStream& stream, TResult invalidResult, const char* sourceName) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "%s answer is not finite", sourceName);
    }
    if (value < MIN_SCORE - EPS || value > MAX_SCORE + EPS) {
        stream.quitf(invalidResult, "%s answer %.12f is outside possible score range", sourceName, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after %s answer", sourceName);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
