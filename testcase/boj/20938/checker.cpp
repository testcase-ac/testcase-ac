#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    double jury = ans.readDouble(0.0, n, "jury answer");
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    double participant = ouf.readDouble(0.0, n, "participant answer");
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    if (!doubleCompare(jury, participant, EPS)) {
        quitf(_wa,
              "expected %.17g, found %.17g, error %.17g",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant);
}
