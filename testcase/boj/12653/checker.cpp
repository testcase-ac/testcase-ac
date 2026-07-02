#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const double EPS = 1e-5;

struct Output {
    vector<double> values;
};

double parseDoubleToken(InStream& stream, const string& token, int caseIndex, TResult invalidVerdict) {
    errno = 0;
    char* end = nullptr;
    double value = strtod(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || errno == ERANGE) {
        stream.quitf(invalidVerdict, "case %d: invalid numeric answer '%s'", caseIndex, token.c_str());
    }
    return value;
}

Output readOutput(InStream& stream, int testCount, TResult invalidVerdict) {
    Output output;
    output.values.reserve(testCount);

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        string caseWord = stream.readWord();
        if (caseWord != "Case") {
            stream.quitf(invalidVerdict, "case %d: expected 'Case', found '%s'", caseIndex, caseWord.c_str());
        }

        string caseNumber = stream.readWord();
        string expectedCaseNumber = format("#%d:", caseIndex);
        if (caseNumber != expectedCaseNumber) {
            stream.quitf(invalidVerdict,
                         "case %d: expected '%s', found '%s'",
                         caseIndex,
                         expectedCaseNumber.c_str(),
                         caseNumber.c_str());
        }

        string answerToken = stream.readWord();
        double value = parseDoubleToken(stream, answerToken, caseIndex, invalidVerdict);
        if (!isfinite(value)) {
            stream.quitf(invalidVerdict, "case %d: answer must be finite", caseIndex);
        }
        if (value < 0.0) {
            stream.quitf(invalidVerdict, "case %d: answer must be nonnegative, found %.17g", caseIndex, value);
        }

        output.values.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after case %d", testCount);
    }

    return output;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    Output jury = readOutput(ans, testCount, _fail);
    Output participant = readOutput(ouf, testCount, _wa);

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        double expected = jury.values[caseIndex - 1];
        double found = participant.values[caseIndex - 1];
        if (!doubleCompare(expected, found, EPS)) {
            quitf(_wa,
                  "case %d: expected %.17g, found %.17g, error %.17g",
                  caseIndex,
                  expected,
                  found,
                  doubleDelta(expected, found));
        }
    }

    quitf(_ok, "all %d cases are within tolerance", testCount);
}
