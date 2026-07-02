#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream) {
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

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);

    double error = fabs(participant - jury);
    if (error <= EPS || error <= EPS * fabs(jury)) {
        quitf(_ok, "answer %.12f is within tolerance", participant);
    }

    quitf(_wa,
          "expected %.12f, found %.12f, absolute error %.12f",
          jury,
          participant,
          error);
}
