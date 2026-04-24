#include "testlib.h"
#include <string>
using namespace std;

const double EPS = 1e-3;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer
    double jans = ans.readDouble();
    ans.readEof();

    // Read the participant's answer
    double pans = ouf.readDouble();
    ouf.readEof();

    // Compare with absolute error tolerance EPS
    if (!doubleCompare(jans, pans, EPS)) {
        quitf(_wa,
              "expected: '%.7f', found: '%.7f', error = '%.7f'",
              jans, pans, doubleDelta(jans, pans));
    }

    quitf(_ok,
          "found '%.7f', expected '%.7f', error '%.7f'",
          pans, jans, doubleDelta(jans, pans));
}
