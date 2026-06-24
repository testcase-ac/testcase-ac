#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-9;

double readAnswer(InStream& stream, TResult verdict) {
    double value = stream.readDouble(0.0, 1e100, "maximum area");
    if (!isfinite(value)) {
        stream.quitf(verdict, "maximum area is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after maximum area");
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
