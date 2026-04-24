#include "testlib.h"
using namespace std;

const double EPS = 1e-2;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the correct answer (jury) and the participant's answer
    double jans = ans.readDouble();
    double pans = ouf.readDouble();

    // Compare with allowed absolute or relative error EPS = 0.01
    if (!doubleCompare(jans, pans, EPS)) {
        quitf(_wa,
              "expected: '%.2f', found: '%.2f', error = '%.2f'",
              jans, pans, doubleDelta(jans, pans));
    }

    quitf(_ok,
          "found '%.2f', expected '%.2f', error = '%.2f'",
          pans, jans, doubleDelta(jans, pans));
}
