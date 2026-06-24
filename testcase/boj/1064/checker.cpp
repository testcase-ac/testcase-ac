#include "testlib.h"

using namespace std;

const double EPS = 1e-9;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double jury = ans.readDouble();
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }

    double participant = ouf.readDouble();
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
