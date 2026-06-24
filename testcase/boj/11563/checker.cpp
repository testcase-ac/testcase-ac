#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult verdict) {
    double value = stream.readDouble(0.0, 1e100, "minimum road length");
    if (!isfinite(value)) {
        stream.quitf(verdict, "minimum road length is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after minimum road length");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa, "expected %.12f, found %.12f", jury, participant);
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
