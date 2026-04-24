#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-2;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int cnt = 0;
    double jans = 0.0, pans = 0.0;
    // There should be exactly one number in the jury answer file
    while (!ans.seekEof()) {
        cnt++;
        jans = ans.readDouble();
        pans = ouf.readDouble();
        if (!doubleCompare(jans, pans, EPS)) {
            quitf(_wa,
                  "number %d differs - expected: '%.6f', found: '%.6f', abs error = '%.6f'",
                  cnt, jans, pans, fabs(jans - pans));
        }
    }
    if (cnt == 0) {
        quitf(_wa, "jury answer is empty");
    }
    // Optionally, check for extra tokens in participant's output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after the answer");
    }
    // If we get here, the answer is correct within the required precision
    quitf(_ok, "answer = '%.6f'", pans);
}
