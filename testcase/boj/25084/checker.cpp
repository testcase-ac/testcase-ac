#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

struct CaseAnswer {
    double value;
};

CaseAnswer readCaseAnswer(InStream& stream, int caseIndex, TResult verdict) {
    string caseWord = stream.readWord();
    if (caseWord != "Case") {
        stream.quitf(verdict, "case %d: expected 'Case', found '%s'", caseIndex, caseWord.c_str());
    }

    string caseNumber = stream.readWord();
    string expectedNumber = format("#%d:", caseIndex);
    if (caseNumber != expectedNumber) {
        stream.quitf(verdict, "case %d: expected '%s', found '%s'",
                     caseIndex, expectedNumber.c_str(), caseNumber.c_str());
    }

    double value = stream.readDouble();
    if (__testlib_isNaN(value) || __testlib_isInfinite(value) || value < 0) {
        stream.quitf(verdict, "case %d: invalid area %.17g", caseIndex, value);
    }
    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        CaseAnswer jury = readCaseAnswer(ans, caseIndex, _fail);
        CaseAnswer participant = readCaseAnswer(ouf, caseIndex, _wa);

        if (!doubleCompare(jury.value, participant.value, EPS)) {
            quitf(_wa,
                  "case %d: expected %.17g, found %.17g, error %.17g",
                  caseIndex, jury.value, participant.value,
                  doubleDelta(jury.value, participant.value));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d cases are within tolerance", t);
}
