#include "testlib.h"

#include <cmath>

using namespace std;

const double REL_EPS = 1e-6;

double readArea(InStream& stream) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(_wa, "area must be finite");
    }
    if (value < 0) {
        stream.quitf(_wa, "area must be non-negative");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after area");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readArea(ans);
    double participant = readArea(ouf);

    double error = fabs(participant - jury);
    double allowed = fabs(jury) * REL_EPS;

    if (error <= allowed) {
        quitf(_ok, "area %.20f is within relative error %.1e", participant, REL_EPS);
    }
    quitf(_wa,
          "expected %.20f, found %.20f, relative error %.20f exceeds %.1e",
          jury,
          participant,
          jury == 0 ? error : error / fabs(jury),
          REL_EPS);
}
