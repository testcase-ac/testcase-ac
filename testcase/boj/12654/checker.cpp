#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const long double EPS = 1e-5L;

long double readFiniteRealToken(InStream& stream, const string& name) {
    string token = stream.readToken();
    const char* begin = token.c_str();
    char* end = nullptr;
    errno = 0;
    long double value = strtold(begin, &end);

    if (begin == end || *end != '\0' || errno == ERANGE || !isfinite(value)) {
        stream.quitf(_wa, "%s is not a finite real number: %s", name.c_str(), token.c_str());
    }

    return value;
}

vector<long double> readOutput(InStream& stream, int testCases) {
    vector<long double> values(testCases + 1);

    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        string caseToken = stream.readToken();
        if (caseToken != "Case") {
            stream.quitf(_wa, "case %d: expected 'Case', found '%s'", caseNum, caseToken.c_str());
        }

        string numberToken = stream.readToken();
        string expectedNumber = format("#%d:", caseNum);
        if (numberToken != expectedNumber) {
            stream.quitf(_wa,
                         "case %d: expected '%s', found '%s'",
                         caseNum,
                         expectedNumber.c_str(),
                         numberToken.c_str());
        }

        values[caseNum] = readFiniteRealToken(stream, format("answer for case %d", caseNum));
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", testCases);
    }
    return values;
}

bool withinTolerance(long double expected, long double actual) {
    long double diff = fabsl(expected - actual);
    long double scale = max(fabsl(expected), 1.0L);
    return diff <= EPS || diff <= EPS * scale;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCases = inf.readInt();
    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        inf.readInt();
        inf.readInt();
    }

    vector<long double> jury = readOutput(ans, testCases);
    vector<long double> participant = readOutput(ouf, testCases);

    for (int caseNum = 1; caseNum <= testCases; ++caseNum) {
        if (!withinTolerance(jury[caseNum], participant[caseNum])) {
            quitf(_wa,
                  "case %d: expected %.15Lf, found %.15Lf",
                  caseNum,
                  jury[caseNum],
                  participant[caseNum]);
        }
    }

    quitf(_ok, "all %d case(s) are within tolerance", testCases);
}
