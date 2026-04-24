#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-3;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j = 0, p = 0;

    // There should be exactly one number in the jury output (the correct width)
    // and exactly one in the contestant output.
    while (!ans.seekEof()) {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS)) {
            quitf(_wa, "%d%s numbers differ - expected: '%.6f', found: '%.6f', error = '%.6f'",
                  n, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
        }
    }

    if (n == 0) {
        quitf(_wa, "no numbers in output");
    } else if (n == 1) {
        quitf(_ok, "found '%.6f', expected '%.6f', error = '%.6f'", p, j, doubleDelta(j, p));
    } else {
        // In theory we expect only one number, but if there are more,
        // and all matched, we still accept.
        quitf(_ok, "%d numbers", n);
    }
}
