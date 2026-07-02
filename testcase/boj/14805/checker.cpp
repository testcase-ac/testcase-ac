#include "testlib.h"
#include <array>
#include <string>
#include <vector>
using namespace std;

struct CaseInput {
    int n;
    array<int, 6> count;
};

struct Claim {
    bool impossible;
    string arrangement;
};

int colorIndex(char c) {
    string colors = "ROYGBV";
    size_t pos = colors.find(c);
    return pos == string::npos ? -1 : int(pos);
}

int hairMask(char c) {
    if (c == 'R') return 1;
    if (c == 'O') return 1 | 2;
    if (c == 'Y') return 2;
    if (c == 'G') return 2 | 4;
    if (c == 'B') return 4;
    if (c == 'V') return 1 | 4;
    return 0;
}

void readCasePrefix(InStream& stream, int expectedCase) {
    string token = stream.readToken();
    string expected = "Case #" + toString(expectedCase) + ":";
    if (token == expected) {
        return;
    }

    if (token == "Case") {
        string number = stream.readToken();
        string expectedNumber = "#" + toString(expectedCase) + ":";
        if (number == expectedNumber) {
            return;
        }
        stream.quitf(_wa, "Case #%d: expected prefix \"%s\", found \"Case %s\"",
                     expectedCase, expected.c_str(), number.c_str());
    }

    stream.quitf(_wa, "Case #%d: expected prefix \"%s\", found \"%s\"",
                 expectedCase, expected.c_str(), token.c_str());
}

Claim readClaim(InStream& stream, const CaseInput& input, int caseIndex) {
    readCasePrefix(stream, caseIndex);
    string answer = stream.readToken();

    if (answer == "IMPOSSIBLE") {
        return {true, ""};
    }

    if (int(answer.size()) != input.n) {
        stream.quitf(_wa, "Case #%d: arrangement length is %d, expected %d",
                     caseIndex, int(answer.size()), input.n);
    }

    array<int, 6> seen{};
    for (int i = 0; i < input.n; ++i) {
        int idx = colorIndex(answer[i]);
        if (idx == -1) {
            stream.quitf(_wa, "Case #%d: invalid color '%c' at position %d",
                         caseIndex, answer[i], i + 1);
        }
        ++seen[idx];
    }

    for (int i = 0; i < 6; ++i) {
        if (seen[i] != input.count[i]) {
            string colors = "ROYGBV";
            stream.quitf(_wa,
                         "Case #%d: color %c count is %d, expected %d",
                         caseIndex, colors[i], seen[i], input.count[i]);
        }
    }

    for (int i = 0; i < input.n; ++i) {
        char a = answer[i];
        char b = answer[(i + 1) % input.n];
        if ((hairMask(a) & hairMask(b)) != 0) {
            stream.quitf(_wa,
                         "Case #%d: adjacent colors %c and %c at positions %d and %d share a hair color",
                         caseIndex, a, b, i + 1, (i + 1) % input.n + 1);
        }
    }

    return {false, answer};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    vector<CaseInput> inputs(tests);
    for (int caseIndex = 0; caseIndex < tests; ++caseIndex) {
        CaseInput current;
        current.n = inf.readInt();
        for (int i = 0; i < 6; ++i) {
            current.count[i] = inf.readInt();
        }
        inputs[caseIndex] = current;
    }

    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        Claim jury = readClaim(ans, inputs[caseIndex - 1], caseIndex);
        Claim participant = readClaim(ouf, inputs[caseIndex - 1], caseIndex);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "Case #%d: participant found a valid arrangement while jury says IMPOSSIBLE",
                  caseIndex);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "Case #%d: jury has a valid arrangement but participant says IMPOSSIBLE",
                  caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "%d case(s) passed", tests);
}
