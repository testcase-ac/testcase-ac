#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the contestant's answer
    double jans = ans.readDouble();
    double pans = ouf.readDouble();

    // Compare with both absolute and relative error tolerance EPS
    if (!doubleCompare(jans, pans, EPS)) {
        quitf(_wa,
              "answer differs - expected: '%.10f', found: '%.10f', error = '%.10f'",
              jans, pans, doubleDelta(jans, pans));
    }

    // Optionally, ensure there's no extra output from the contestant
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after the answer");
    }

    quitf(_ok,
          "correct - expected: '%.10f', found: '%.10f', error = '%.10f'",
          jans, pans, doubleDelta(jans, pans));
}
