#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-8;

double readAnswer(InStream& stream, TResult invalidResult) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidResult, "answer must be finite, found %.17g", value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after answer");
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
