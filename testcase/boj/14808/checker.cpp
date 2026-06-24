#include "testlib.h"
#include <cmath>
#include <string>
#include <vector>
using namespace std;

const double EPS = 1e-6;

struct Output {
    vector<vector<double>> values;
};

void quitStream(InStream &stream, TResult outcome, const string &message) {
    stream.quitf(outcome, "%s", message.c_str());
}

string readCasePrefix(InStream &stream, int expectedCase, TResult outcome) {
    string token = stream.readToken();
    string expected = "Case #" + toString(expectedCase) + ":";
    if (token == expected) {
        return token;
    }

    string splitExpected = "Case";
    if (token == splitExpected) {
        string number = stream.readToken();
        string expectedNumber = "#" + toString(expectedCase) + ":";
        if (number == expectedNumber) {
            return token + " " + number;
        }
    }

    quitStream(stream, outcome,
               format("expected case prefix \"%s\", found \"%s\"",
                      expected.c_str(), token.c_str()));
    return token;
}

double readFiniteDouble(InStream &stream, TResult outcome, const string &name) {
    double value = stream.readDouble();
    if (!isfinite(value)) {
        quitStream(stream, outcome, format("%s is not finite", name.c_str()));
    }
    return value;
}

Output readOutput(InStream &stream, TResult outcome, const vector<int> &queryCounts) {
    Output output;
    output.values.resize(queryCounts.size());

    for (int tc = 0; tc < int(queryCounts.size()); ++tc) {
        readCasePrefix(stream, tc + 1, outcome);
        output.values[tc].resize(queryCounts[tc]);
        for (int i = 0; i < queryCounts[tc]; ++i) {
            output.values[tc][i] =
                readFiniteDouble(stream, outcome,
                                 format("Case #%d answer %d", tc + 1, i + 1));
        }
    }

    if (!stream.seekEof()) {
        quitStream(stream, outcome, "extra output after the last answer");
    }
    return output;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    vector<int> queryCounts(tests);
    for (int tc = 0; tc < tests; ++tc) {
        int n = inf.readInt();
        int q = inf.readInt();
        queryCounts[tc] = q;

        for (int i = 0; i < n; ++i) {
            inf.readLong();
            inf.readLong();
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inf.readLong();
            }
        }
        for (int i = 0; i < q; ++i) {
            inf.readInt();
            inf.readInt();
        }
    }

    Output jury = readOutput(ans, _fail, queryCounts);
    Output participant = readOutput(ouf, _wa, queryCounts);

    for (int tc = 0; tc < tests; ++tc) {
        for (int i = 0; i < queryCounts[tc]; ++i) {
            double expected = jury.values[tc][i];
            double found = participant.values[tc][i];
            if (!doubleCompare(expected, found, EPS)) {
                quitf(_wa,
                      "Case #%d answer %d differs: expected %.12f, found %.12f, error %.12f",
                      tc + 1, i + 1, expected, found, doubleDelta(expected, found));
            }
        }
    }

    quitf(_ok, "all %d case(s) are within tolerance", tests);
}
