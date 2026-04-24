#include "testlib.h"
#include <iostream>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the participant's answer
    double j = ans.readDouble();
    double p = ouf.readDouble();

    // Compare with given absolute or relative error EPS
    if (!doubleCompare(j, p, EPS)) {
        quitf(_wa,
              "expected: '%.10f', found: '%.10f', error = '%.10f'",
              j, p, doubleDelta(j, p));
    }

    // If correct, report OK
    quitf(_ok,
          "expected: '%.10f', found: '%.10f', error = '%.10f'",
          j, p, doubleDelta(j, p));
}
