#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-9;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read jury's answer and participant's answer
    double j = ans.readDouble();
    double p = ouf.readDouble();

    // Compare within the required tolerance
    if (!doubleCompare(j, p, EPS)) {
        quitf(_wa,
              "wrong answer: expected '%.10f', found '%.10f', "
              "error = '%.10f'",
              j, p, doubleDelta(j, p));
    }

    // Ensure there's no extra output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output");
    }

    quitf(_ok, "correct");
    return 0;
}
