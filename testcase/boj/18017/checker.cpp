#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-9;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the contestant's answer
    double j = ans.readDouble();
    double p = ouf.readDouble();

    // Check for extra output from the contestant
    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens after the answer");
    }

    // Compare with given precision
    if (!doubleCompare(j, p, EPS)) {
        quitf(_wa,
              "numbers differ - expected: '%.10f', found: '%.10f', error = '%.10f'",
              j, p, doubleDelta(j, p));
    }

    // OK
    quitf(_ok,
          "found '%.10f', expected '%.10f', error = '%.10f'",
          p, j, doubleDelta(j, p));
}
