#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

double readCaseAnswer(InStream& stream, int caseNo, TResult invalidResult) {
    string caseWord = stream.readToken();
    if (caseWord != "Case") {
        stream.quitf(invalidResult, "case %d: expected 'Case', found '%s'", caseNo, caseWord.c_str());
    }

    string caseLabel = stream.readToken();
    string expectedLabel = format("#%d:", caseNo);
    if (caseLabel != expectedLabel) {
        stream.quitf(invalidResult, "case %d: expected '%s', found '%s'", caseNo, expectedLabel.c_str(), caseLabel.c_str());
    }

    double value = stream.readDouble();
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    for (int caseNo = 1; caseNo <= tests; ++caseNo) {
        double jury = readCaseAnswer(ans, caseNo, _fail);
        double participant = readCaseAnswer(ouf, caseNo, _wa);

        if (!doubleCompare(jury, participant, EPS)) {
            quitf(_wa,
                  "case %d: expected %.12f, found %.12f, error %.12f",
                  caseNo,
                  jury,
                  participant,
                  doubleDelta(jury, participant));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all answers are within tolerance");
}
