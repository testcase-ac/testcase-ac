#include "testlib.h"

#include <cmath>

using namespace std;

namespace {

const double EPS = 1e-2;

double readArea(InStream& stream, TResult invalidVerdict, const char* streamName) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(invalidVerdict, "%s area is not finite", streamName);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s area", streamName);
    }
    return value;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readArea(ans, _fail, "jury");
    double participant = readArea(ouf, _wa, "participant");

    double error = fabs(participant - jury);
    if (error > EPS) {
        quitf(_wa, "expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
              jury, participant, error, EPS);
    }

    quitf(_ok, "answer %.10f is within %.10f of jury answer %.10f",
          participant, EPS, jury);
}
