#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    array<int, 6> need;
};

struct Answer {
    bool impossible;
};

vector<TestCase> cases;

int colorIndex(char c) {
    if (c == 'R') return 0;
    if (c == 'O') return 1;
    if (c == 'Y') return 2;
    if (c == 'G') return 3;
    if (c == 'B') return 4;
    if (c == 'V') return 5;
    return -1;
}

int colorMask(char c) {
    if (c == 'R') return 1;
    if (c == 'O') return 1 | 2;
    if (c == 'Y') return 2;
    if (c == 'G') return 2 | 4;
    if (c == 'B') return 4;
    if (c == 'V') return 1 | 4;
    return 0;
}

vector<Answer> readAnswer(InStream& stream) {
    vector<Answer> answers;
    answers.reserve(cases.size());

    for (int tc = 1; tc <= (int)cases.size(); ++tc) {
        string caseToken = stream.readToken();
        if (caseToken != "Case") {
            stream.quitf(_wa, "case %d: expected 'Case', found '%s'", tc, caseToken.c_str());
        }

        string numberToken = stream.readToken();
        string expectedNumber = "#" + to_string(tc) + ":";
        if (numberToken != expectedNumber) {
            stream.quitf(_wa, "case %d: expected '%s', found '%s'",
                         tc, expectedNumber.c_str(), numberToken.c_str());
        }

        string token = stream.readToken();
        if (token == "IMPOSSIBLE") {
            answers.push_back({true});
            continue;
        }

        const TestCase& test = cases[tc - 1];
        if ((int)token.size() != test.n) {
            stream.quitf(_wa, "case %d: arrangement length is %d, expected %d",
                         tc, (int)token.size(), test.n);
        }

        array<int, 6> seen{};
        for (int i = 0; i < test.n; ++i) {
            int idx = colorIndex(token[i]);
            if (idx < 0) {
                stream.quitf(_wa, "case %d: invalid color '%c' at position %d",
                             tc, token[i], i + 1);
            }
            ++seen[idx];
        }

        for (int i = 0; i < 6; ++i) {
            if (seen[i] != test.need[i]) {
                stream.quitf(_wa, "case %d: color count %d is %d, expected %d",
                             tc, i + 1, seen[i], test.need[i]);
            }
        }

        for (int i = 0; i < test.n; ++i) {
            int j = (i + 1) % test.n;
            if ((colorMask(token[i]) & colorMask(token[j])) != 0) {
                stream.quitf(_wa, "case %d: adjacent positions %d and %d share a hair color",
                             tc, i + 1, j + 1);
            }
        }

        answers.push_back({false});
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d cases", (int)cases.size());
    }

    return answers;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        cases[tc].n = inf.readInt();
        for (int i = 0; i < 6; ++i) {
            cases[tc].need[i] = inf.readInt();
        }
    }

    vector<Answer> jury = readAnswer(ans);
    vector<Answer> participant = readAnswer(ouf);

    for (int tc = 1; tc <= t; ++tc) {
        if (jury[tc - 1].impossible) {
            if (!participant[tc - 1].impossible) {
                quitf(_fail, "case %d: participant found a valid arrangement while jury reports impossible", tc);
            }
            continue;
        }

        if (participant[tc - 1].impossible) {
            quitf(_wa, "case %d: participant reports impossible, but jury has a valid arrangement", tc);
        }
    }

    quitf(_ok, "all cases are valid");
}
