#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream) {
    double value = stream.readDouble(0.0, 1.0, "probability");
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
    double error = fabs(jury - participant);

    if (error < EPS) {
        quitf(_ok, "answer %.17g is within absolute tolerance", participant);
    }
    quitf(_wa,
          "expected %.17g, found %.17g, absolute error %.17g",
          jury,
          participant,
          error);
}
