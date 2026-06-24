#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-3;

double readSingleValue(InStream& stream, TResult invalidResult, const char* name) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        quitf(invalidResult, "%s is not finite", name);
    }
    if (!stream.seekEof()) {
        quitf(invalidResult, "extra output after %s", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readSingleValue(ans, _fail, "jury answer");
    double participant = readSingleValue(ouf, _wa, "participant answer");
    double error = fabs(participant - jury);

    if (error > EPS + 1e-12) {
        quitf(_wa,
              "expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
              jury,
              participant,
              error,
              EPS);
    }

    quitf(_ok, "answer %.10f is within absolute error %.10f", participant, EPS);
}
