#include "testlib.h"

#include <cmath>
using namespace std;

const double EPS = 1e-6;
const double MIN_VALUE = 0.0;
const double MAX_VALUE = 9.0;
const double RANGE_SLACK = 1e-9;

double readClaim(InStream& stream, int caseIndex) {
    double value = stream.readDouble(-1e100, 1e100, format("answer[%d]", caseIndex));
    if (!isfinite(value)) {
        stream.quitf(_wa, "answer[%d] is not finite", caseIndex);
    }
    if (value < MIN_VALUE - RANGE_SLACK || value > MAX_VALUE + RANGE_SLACK) {
        stream.quitf(_wa, "answer[%d] = %.17g is outside [0, 9]", caseIndex, value);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        int h = inf.readInt();
        int w = inf.readInt();
        (void)w;
        for (int row = 0; row < h; ++row) {
            inf.readToken();
        }

        double jury = readClaim(ans, tc);
        double participant = readClaim(ouf, tc);

        if (!doubleCompare(jury, participant, EPS)) {
            quitf(_wa,
                  "answer[%d] expected %.17g, found %.17g, error %.17g",
                  tc, jury, participant, doubleDelta(jury, participant));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all answers are within tolerance");
}
