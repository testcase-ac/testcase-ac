#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-4;

double readAnswer(InStream& stream, TResult extraVerdict) {
    double value = stream.readDouble(-1e100, 1e100, "probability");
    if (!isfinite(value)) {
        stream.quitf(extraVerdict, "probability is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(extraVerdict, "extra output after probability");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa, "expected %.12f, found %.12f, error %.12f",
              jury, participant, doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
