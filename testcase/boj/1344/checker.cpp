#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the participant's answer: one double each.
    if (ans.seekEof()) {
        quitf(_fail, "jury output is empty");
    }
    double j = ans.readDouble();
    if (ouf.seekEof()) {
        quitf(_wa, "participant output is empty");
    }
    double p = ouf.readDouble();

    // Check for any extra tokens in participant output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens in participant output");
    }

    // Compare within absolute/relative error EPS
    if (!doubleCompare(j, p, EPS)) {
        quitf(_wa, "answer mismatch - expected: '%.10f', found: '%.10f', diff = '%.10f'",
              j, p, doubleDelta(j, p));
    }

    quitf(_ok, "correct answer: '%.10f'", p);
}
