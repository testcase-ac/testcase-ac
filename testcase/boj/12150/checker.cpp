#include "testlib.h"
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const double EPS = 1e-6;

struct Answer {
    vector<double> values;
};

void quitStream(InStream &stream, TResult result, const string &message) {
    stream.quitf(result, "%s", message.c_str());
}

void readCasePrefix(InStream &stream, int expectedCase, TResult result) {
    string expected = "Case #" + toString(expectedCase) + ":";
    string first = stream.readToken();
    if (first == expected) {
        return;
    }

    if (first == "Case") {
        string second = stream.readToken();
        string expectedSecond = "#" + toString(expectedCase) + ":";
        if (second == expectedSecond) {
            return;
        }
        quitStream(stream, result,
                   format("Case #%d: expected prefix \"%s\", found \"Case %s\"",
                          expectedCase, expected.c_str(), second.c_str()));
    }

    quitStream(stream, result,
               format("Case #%d: expected prefix \"%s\", found \"%s\"",
                      expectedCase, expected.c_str(), first.c_str()));
}

Answer readAnswer(InStream &stream, TResult result, int tests) {
    Answer answer;
    answer.values.reserve(tests);

    for (int tc = 1; tc <= tests; ++tc) {
        readCasePrefix(stream, tc, result);
        double value = stream.readDouble();
        if (!isfinite(value)) {
            quitStream(stream, result,
                       format("Case #%d: answer is not finite", tc));
        }
        answer.values.push_back(value);
    }

    if (!stream.seekEof()) {
        quitStream(stream, result, "extra output after the last answer");
    }

    return answer;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();

    Answer jury = readAnswer(ans, _fail, tests);
    Answer participant = readAnswer(ouf, _wa, tests);

    for (int tc = 0; tc < tests; ++tc) {
        double expected = jury.values[tc];
        double found = participant.values[tc];
        if (!doubleCompare(expected, found, EPS)) {
            quitf(_wa,
                  "Case #%d: expected %.12f, found %.12f, error %.12f",
                  tc + 1, expected, found, doubleDelta(expected, found));
        }
    }

    quitf(_ok, "all %d case(s) are within tolerance", tests);
}
