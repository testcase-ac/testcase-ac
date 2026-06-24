#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    const double EPS = 1e-5;

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
              "expected %.10f, found %.10f, error %.10f",
              jury,
              participant,
              doubleDelta(jury, participant));
    }

    quitf(_ok, "answer %.10f is within tolerance", participant);
}
