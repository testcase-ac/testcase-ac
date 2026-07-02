#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult invalidVerdict, const char* source) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        quitf(invalidVerdict, "%s answer is not finite", source);
    }
    if (value < 0.0) {
        quitf(invalidVerdict, "%s answer %.17g is negative", source, value);
    }
    if (!stream.seekEof()) {
        quitf(invalidVerdict, "extra output after %s answer", source);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    double error = fabs(jury - participant);
    if (error > EPS) {
        quitf(_wa,
              "expected %.17g, found %.17g, absolute error %.17g",
              jury,
              participant,
              error);
    }

    quitf(_ok, "answer %.17g is within absolute tolerance", participant);
}
