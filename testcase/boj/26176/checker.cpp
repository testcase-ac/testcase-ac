#include "testlib.h"
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j = 0, p = 0;

    // We expect exactly one double in the jury's answer.
    // This loop will run once, comparing that one number.
    while (!ans.seekEof()) {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS)) {
            quitf(_wa, "%d%s number differs - expected: '%.10f', found: '%.10f', error = '%.10f'",
                  n, englishEnding(n).c_str(), j, p, doubleDelta(j, p));
        }
    }

    if (n == 0) {
        quitf(_wa, "no number found in the output");
    } else if (n == 1) {
        quitf(_ok, "found '%.10f', expected '%.10f', error '%.10f'", p, j, doubleDelta(j, p));
    } else {
        // In principle there should be only one number, but if more are present
        // and all match, we still accept.
        quitf(_ok, "%d numbers matched", n);
    }

    return 0;
}
