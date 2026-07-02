#include "testlib.h"
#include <array>
#include <string>
#include <vector>
using namespace std;

struct Claim {
    bool impossible;
    string answer;
};

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

Claim readClaim(InStream& stream, const string& input, int caseIndex) {
    readCasePrefix(stream, caseIndex);
    string answer = stream.readToken();

    if (answer == "IMPOSSIBLE") {
        return {true, ""};
    }

    if (answer.size() != input.size()) {
        stream.quitf(_wa, "Case #%d: answer length is %d, expected %d",
                     caseIndex, int(answer.size()), int(input.size()));
    }

    array<int, 26> expected{};
    array<int, 26> seen{};
    for (char c : input) {
        ++expected[c - 'a'];
    }

    for (int i = 0; i < int(answer.size()); ++i) {
        char c = answer[i];
        if (c < 'a' || c > 'z') {
            stream.quitf(_wa, "Case #%d: invalid character '%c' at position %d",
                         caseIndex, c, i + 1);
        }
        if (c == input[i]) {
            stream.quitf(_wa, "Case #%d: position %d keeps letter '%c'",
                         caseIndex, i + 1, c);
        }
        ++seen[c - 'a'];
    }

    for (int i = 0; i < 26; ++i) {
        if (seen[i] != expected[i]) {
            stream.quitf(_wa,
                         "Case #%d: letter '%c' count is %d, expected %d",
                         caseIndex, char('a' + i), seen[i], expected[i]);
        }
    }

    return {false, answer};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    vector<string> inputs(tests);
    for (int caseIndex = 0; caseIndex < tests; ++caseIndex) {
        inputs[caseIndex] = inf.readToken();
    }

    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        Claim jury = readClaim(ans, inputs[caseIndex - 1], caseIndex);
        Claim participant = readClaim(ouf, inputs[caseIndex - 1], caseIndex);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "Case #%d: participant found a valid answer while jury says IMPOSSIBLE",
                  caseIndex);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "Case #%d: jury has a valid answer but participant says IMPOSSIBLE",
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
