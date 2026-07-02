#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

struct Answer {
    vector<double> values;
};

Answer readAnswer(InStream& stream, int testCount) {
    Answer answer;
    answer.values.reserve(testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        string caseToken = stream.readToken();
        if (caseToken != "Case") {
            stream.quitf(_wa, "expected 'Case' for test %d, found '%s'", tc, caseToken.c_str());
        }

        string numberToken = stream.readToken();
        string expectedNumber = format("#%d:", tc);
        if (numberToken != expectedNumber) {
            stream.quitf(_wa, "expected '%s' for test %d, found '%s'", expectedNumber.c_str(), tc, numberToken.c_str());
        }

        answer.values.push_back(stream.readDouble());
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d test cases", testCount);
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    Answer jury = readAnswer(ans, testCount);
    Answer participant = readAnswer(ouf, testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        double expected = jury.values[tc - 1];
        double found = participant.values[tc - 1];
        if (!doubleCompare(expected, found, EPS)) {
            quitf(_wa,
                  "test %d: expected %.12f, found %.12f, error %.12f",
                  tc,
                  expected,
                  found,
                  doubleDelta(expected, found));
        }
    }

    quitf(_ok, "all %d answer(s) are within tolerance", testCount);
}
