#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-8;

double readAnswer(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "probability is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after probability");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans);
    double participant = readAnswer(ouf);
    double error = fabs(participant - jury);

    if (error <= EPS) {
        quitf(_ok, "answer %.12f is within absolute error %.12g", participant, error);
    }
    quitf(_wa, "expected %.12f, found %.12f, absolute error %.12g exceeds %.12g",
          jury, participant, error, EPS);
}
