#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Answer {
    vector<vector<double>> roots;
};

double parseNumber(const string& token, InStream& stream, int tc, int index) {
    char* end = nullptr;
    errno = 0;
    double value = strtod(token.c_str(), &end);
    if (end != token.c_str() + token.size() || errno == ERANGE || !isfinite(value)) {
        stream.quitf(_wa, "case %d root %d is not a finite number: %s",
                     tc, index, token.c_str());
    }
    return value;
}

Answer readAnswer(InStream& stream, int testCount) {
    Answer answer;
    answer.roots.resize(testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        string line = stream.readLine();
        stringstream ss(line);
        vector<double> roots;
        string token;

        while (ss >> token) {
            if (roots.size() == 3) {
                stream.quitf(_wa, "case %d has more than 3 roots", tc);
            }
            roots.push_back(parseNumber(token, stream, tc, (int)roots.size() + 1));
        }

        if (roots.empty()) {
            stream.quitf(_wa, "case %d has no roots", tc);
        }

        for (int i = 1; i < (int)roots.size(); ++i) {
            if (!(roots[i - 1] < roots[i])) {
                stream.quitf(_wa,
                             "case %d roots are not strictly increasing at positions %d and %d: %.17g %.17g",
                             tc, i, i + 1, roots[i - 1], roots[i]);
            }
        }

        answer.roots[tc - 1] = roots;
    }

    stream.readEof();
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    Answer jury = readAnswer(ans, testCount);
    Answer participant = readAnswer(ouf, testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        const vector<double>& expected = jury.roots[tc - 1];
        const vector<double>& actual = participant.roots[tc - 1];

        if (actual.size() != expected.size()) {
            quitf(_wa, "case %d expected %d roots, found %d roots",
                  tc, (int)expected.size(), (int)actual.size());
        }

        for (int i = 0; i < (int)expected.size(); ++i) {
            if (!doubleCompare(expected[i], actual[i], EPS)) {
                quitf(_wa,
                      "case %d root %d differs: expected %.17g, found %.17g, error %.17g",
                      tc, i + 1, expected[i], actual[i], doubleDelta(expected[i], actual[i]));
            }
        }
    }

    quitf(_ok, "all roots are within tolerance");
}
