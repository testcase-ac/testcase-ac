#include "testlib.h"

#include <algorithm>
#include <cmath>

using namespace std;

const long double EPS = 1e-6L;

long double readAnswer(InStream& stream) {
    long double value = stream.readDouble(0.0, 1e100, "answer");
    if (!isfinite((double)value)) {
        stream.quitf(_wa, "answer must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long double jury = readAnswer(ans);
    long double participant = readAnswer(ouf);

    long double denominator = max(jury, 1.0L);
    long double relativeError = fabsl(participant - jury) / denominator;

    if (relativeError <= EPS) {
        quitf(_ok, "answer %.15Lf is within relative tolerance", participant);
    }

    quitf(_wa,
          "expected %.15Lf, found %.15Lf, relative error %.15Lf",
          jury,
          participant,
          relativeError);
}
