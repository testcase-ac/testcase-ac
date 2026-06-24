#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readProbability(InStream& stream, TResult invalidVerdict, const char* owner) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidVerdict, "%s answer is not finite", owner);
    }
    if (value < -EPS || value > 1.0 + EPS) {
        stream.quitf(invalidVerdict, "%s answer %.17g is outside probability range [0, 1]", owner, value);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s answer", owner);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readProbability(ans, _fail, "jury");
    double participant = readProbability(ouf, _wa, "participant");

    double error = fabs(jury - participant);
    if (error > EPS) {
        quitf(_wa,
              "expected %.17g, found %.17g, absolute error %.17g exceeds %.17g",
              jury,
              participant,
              error,
              EPS);
    }

    quitf(_ok, "answer %.17g is within absolute error %.17g", participant, EPS);
}
