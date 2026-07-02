#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult verdict, const char* streamName) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        quitf(verdict, "%s answer is not finite", streamName);
    }
    if (!stream.seekEof()) {
        quitf(verdict, "extra output after %s answer", streamName);
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
