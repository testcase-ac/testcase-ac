#include "testlib.h"

#include <cmath>
#include <string>

using namespace std;

const double EPS = 1e-3;

struct CaseAnswer {
    double value;
};

CaseAnswer readCaseAnswer(InStream& stream, int caseNo) {
    stream.readToken("Case", "case label");
    stream.readToken(format("#%d:", caseNo), "case number");
    double value = stream.readDouble(-1e100, 1e100, "answer value");
    stream.readEoln();

    if (!isfinite(value)) {
        stream.quitf(_wa, "case %d answer value must be finite", caseNo);
    }
    if (value < 0.0) {
        stream.quitf(_wa, "case %d answer value must be non-negative, found %.10f", caseNo, value);
    }

    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();

    for (int tc = 1; tc <= T; ++tc) {
        CaseAnswer jury = readCaseAnswer(ans, tc);
        CaseAnswer participant = readCaseAnswer(ouf, tc);

        if (!doubleCompare(jury.value, participant.value, EPS)) {
            quitf(_wa,
                  "case %d expected %.10f, found %.10f, error %.10f",
                  tc,
                  jury.value,
                  participant.value,
                  doubleDelta(jury.value, participant.value));
        }
    }

    ans.readEof();
    ouf.readEof();

    quitf(_ok, "all %d case(s) are within tolerance", T);
}
