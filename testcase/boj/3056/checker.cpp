#include "testlib.h"
#include <string>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int count = 0;
    double juryAns = 0.0, partAns = 0.0;

    // We expect exactly one double in the jury answer.
    // We read until EOF of jury stream; for each value we read the participant's.
    while (!ans.seekEof()) {
        count++;
        juryAns = ans.readDouble();
        partAns = ouf.readDouble();

        if (!doubleCompare(juryAns, partAns, EPS)) {
            quitf(_wa,
                  "%d%s numbers differ - expected: '%.6f', found: '%.6f', error = '%.6f'",
                  count, englishEnding(count).c_str(),
                  juryAns, partAns, doubleDelta(juryAns, partAns));
        }
    }

    // If the jury had exactly one number, report OK with details.
    if (count == 1) {
        quitf(_ok,
              "found '%.6f', expected '%.6f', error = '%.6f'",
              partAns, juryAns, doubleDelta(juryAns, partAns));
    }

    // Otherwise, still OK, reporting how many numbers were checked.
    quitf(_ok, "%d numbers", count);
}
