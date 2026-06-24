#include "testlib.h"

using namespace std;

const double EPS = 1e-2;

double readAnswer(InStream& stream, TResult outcome, const char* name) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(outcome, "%s answer is not finite", name);
    }
    if (value < 0) {
        stream.quitf(outcome, "%s answer is negative: %.17g", name, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(outcome, "extra output after %s answer", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.10f, found %.10f, error %.10f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.10f is within tolerance", participant);
}
