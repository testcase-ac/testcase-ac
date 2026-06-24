#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-2;

vector<double> readAnswers(InStream& stream, int testCases) {
    vector<double> values(testCases);
    for (int caseIndex = 1; caseIndex <= testCases; ++caseIndex) {
        values[caseIndex - 1] = stream.readDouble();
        if (!isfinite(values[caseIndex - 1])) {
            stream.quitf(_wa, "answer[%d] is not finite", caseIndex);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answer(s)", testCases);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCases = inf.readInt();

    vector<double> jury = readAnswers(ans, testCases);
    vector<double> participant = readAnswers(ouf, testCases);

    for (int caseIndex = 1; caseIndex <= testCases; ++caseIndex) {
        double expected = jury[caseIndex - 1];
        double found = participant[caseIndex - 1];
        if (!doubleCompare(expected, found, EPS)) {
            quitf(_wa,
                  "answer[%d] expected %.12f, found %.12f, error %.12f",
                  caseIndex,
                  expected,
                  found,
                  doubleDelta(expected, found));
        }
    }

    quitf(_ok, "all %d answer(s) are within absolute or relative error %.1e", testCases, EPS);
}
