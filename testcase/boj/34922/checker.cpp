#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-2;

double readAnswer(InStream& stream, TResult outcome) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        stream.quitf(outcome, "area must be finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(outcome, "extra output after area");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = readAnswer(ans, _fail);
    double participant = readAnswer(ouf, _wa);

    bool absoluteOk = jury - EPS <= participant && participant <= jury + EPS;
    bool relativeOk = 0.99 * jury <= participant && participant <= 1.01 * jury;
    if (!absoluteOk && !relativeOk) {
        quitf(_wa, "expected %.10f, found %.10f", jury, participant);
    }

    quitf(_ok, "answer %.10f is within tolerance of %.10f", participant, jury);
}
