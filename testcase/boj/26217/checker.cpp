#include "testlib.h"

#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 1e-4;

double readAnswer(InStream &stream, TResult verdict, const char *name) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(verdict, "%s answer is not finite", name);
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s answer", name);
    }
    return value;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail, "jury");
    double participant = readAnswer(ouf, _wa, "participant");

    double error = fabs(participant - jury) / max(1.0, fabs(jury));
    if (error > EPS) {
        quitf(_wa,
              "expected %.17g, found %.17g, relative/absolute error %.17g exceeds %.17g",
              jury, participant, error, EPS);
    }

    quitf(_ok, "answer %.17g is within tolerance %.17g", participant, EPS);
}
