#include "testlib.h"

#include <cmath>
using namespace std;

const double EPS = 1e-6;

double readValue(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readValue(ans);
    double participant = readValue(ouf);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.12f, found %.12f, error %.12f",
              jury, participant, doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.12f is within tolerance", participant);
}
