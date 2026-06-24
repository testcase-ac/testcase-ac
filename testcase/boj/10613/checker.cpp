#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-3;

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

    double error = fabs(jury - participant);
    if (error > EPS) {
        quitf(_wa,
              "expected %.10f, found %.10f, absolute error %.10f exceeds %.10f",
              jury,
              participant,
              error,
              EPS);
    }

    quitf(_ok, "answer %.10f is within absolute tolerance %.10f", participant, EPS);
}
