#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const double EPS = 1e-3;

static TResult verdictFor(InStream& stream) {
    return (&stream == &ouf) ? _wa : _fail;
}

static double readFiniteDouble(InStream& stream, int tc) {
    string token = stream.readToken();
    char* end = nullptr;
    errno = 0;
    double value = strtod(token.c_str(), &end);
    if (end != token.c_str() + token.size() || errno == ERANGE || !isfinite(value)) {
        stream.quitf(verdictFor(stream),
                     "case %d: invalid finite number '%s'",
                     tc, token.c_str());
    }
    return value;
}

static vector<double> readOutput(InStream& stream, int testCases) {
    vector<double> values(testCases);
    for (int tc = 1; tc <= testCases; ++tc) {
        string caseToken = stream.readToken();
        if (caseToken != "Case") {
            stream.quitf(verdictFor(stream),
                         "case %d: expected token 'Case', found '%s'",
                         tc, caseToken.c_str());
        }

        string numberToken = stream.readToken();
        string expectedNumberToken = format("#%d:", tc);
        if (numberToken != expectedNumberToken) {
            stream.quitf(verdictFor(stream),
                         "case %d: expected token '%s', found '%s'",
                         tc, expectedNumberToken.c_str(), numberToken.c_str());
        }

        values[tc - 1] = readFiniteDouble(stream, tc);
    }

    if (!stream.seekEof()) {
        stream.quitf(verdictFor(stream), "extra output after %d cases", testCases);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCases = inf.readInt();
    vector<double> jury = readOutput(ans, testCases);
    vector<double> participant = readOutput(ouf, testCases);

    for (int tc = 1; tc <= testCases; ++tc) {
        double expected = jury[tc - 1];
        double found = participant[tc - 1];
        if (!doubleCompare(expected, found, EPS)) {
            quitf(_wa,
                  "case %d: expected %.10f, found %.10f, error %.10f",
                  tc, expected, found, doubleDelta(expected, found));
        }
    }

    quitf(_ok, "all %d cases are within tolerance", testCases);
}
