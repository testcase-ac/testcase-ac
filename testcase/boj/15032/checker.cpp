#include "testlib.h"

#include <cmath>

using namespace std;

const double EPS = 1e-6;

double readAnswer(InStream& stream, TResult verdict, int n) {
    double value = stream.readDouble(0.0, n, "expected heads");
    if (!isfinite(value)) {
        stream.quitf(verdict, "expected heads is not finite");
    }
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after expected heads");
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    double jury = readAnswer(ans, _fail, n);
    double participant = readAnswer(ouf, _wa, n);

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
