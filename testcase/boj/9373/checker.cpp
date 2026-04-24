#include "testlib.h"
#include <string>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int idx = 0;
    // Compare each jury & participant answer line by line
    while (!ans.seekEof()) {
        idx++;
        double j = ans.readDouble();
        double p = ouf.readDouble();
        if (!doubleCompare(j, p, EPS)) {
            quitf(_wa,
                  "%d%s numbers differ - expected: '%.6f', found: '%.6f', error = '%.6f'",
                  idx, englishEnding(idx).c_str(), j, p, doubleDelta(j, p));
        }
    }
    // Check that participant has no extra output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output");
    }
    quitf(_ok, "%d numbers", idx);
}
