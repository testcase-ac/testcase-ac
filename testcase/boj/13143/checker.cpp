#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-3;

struct Answer {
    double value;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict, const char* who, double upperBound) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidVerdict, "%s answer is not finite", who);
    }
    if (value < -EPS) {
        stream.quitf(invalidVerdict, "%s answer is negative: %.10f", who, value);
    }
    if (value > upperBound + EPS) {
        stream.quitf(invalidVerdict,
                     "%s answer exceeds maximum possible count: %.10f > %.10f",
                     who,
                     value,
                     upperBound);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s answer", who);
    }
    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    double upperBound = 1.0 * n * (n - 1) / 2.0;

    Answer jury = readAnswer(ans, _fail, "jury", upperBound);
    Answer participant = readAnswer(ouf, _wa, "participant", upperBound);

    double error = fabs(participant.value - jury.value);
    if (error <= EPS + 1e-12) {
        quitf(_ok,
              "answer %.10f is within absolute tolerance of jury %.10f",
              participant.value,
              jury.value);
    }

    quitf(_wa,
          "expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
          jury.value,
          participant.value,
          error,
          EPS);
}
