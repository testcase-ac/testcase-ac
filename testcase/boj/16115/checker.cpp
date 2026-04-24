#include "testlib.h"
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the contestant's answer (one double each).
    double j = ans.readDouble();
    double p = ouf.readDouble();

    // Compare with the required precision.
    if (!doubleCompare(j, p, EPS)) {
        quitf(_wa, "wrong answer - expected: '%.6f', found: '%.6f', error = '%.6f'",
              j, p, doubleDelta(j, p));
    }

    // If it's OK, report OK.
    quitf(_ok, "%.6f", p);
}
