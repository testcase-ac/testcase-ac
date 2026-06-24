#include "testlib.h"

#include <array>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

const long long TOTAL_INK = 1000000;

struct TestCase {
    array<long long, 4> limit;
};

struct Claim {
    bool impossible;
    array<long long, 4> ink;
};

vector<TestCase> tests;

long long parseNonNegativeIntToken(InStream& stream, const string& token, const string& name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s must be a non-negative integer, found '%s'", name.c_str(), token.c_str());
        }
    }

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > TOTAL_INK) {
            stream.quitf(_wa, "%s exceeds %lld", name.c_str(), TOTAL_INK);
        }
    }
    return value;
}

void readCasePrefix(InStream& stream, int caseNo) {
    string caseWord = stream.readToken();
    if (caseWord != "Case") {
        stream.quitf(_wa, "case %d: expected 'Case', found '%s'", caseNo, caseWord.c_str());
    }

    string caseLabel = stream.readToken();
    string expected = format("#%d:", caseNo);
    if (caseLabel != expected) {
        stream.quitf(_wa, "case %d: expected '%s', found '%s'", caseNo, expected.c_str(), caseLabel.c_str());
    }
}

Claim readClaim(InStream& stream, int caseNo) {
    readCasePrefix(stream, caseNo);

    string first = stream.readToken();
    if (first == "IMPOSSIBLE") {
        return {true, {0, 0, 0, 0}};
    }

    Claim claim;
    claim.impossible = false;
    claim.ink[0] = parseNonNegativeIntToken(stream, first, format("c for case %d", caseNo));
    claim.ink[1] = stream.readLong(0, TOTAL_INK, format("m for case %d", caseNo).c_str());
    claim.ink[2] = stream.readLong(0, TOTAL_INK, format("y for case %d", caseNo).c_str());
    claim.ink[3] = stream.readLong(0, TOTAL_INK, format("k for case %d", caseNo).c_str());

    long long sum = 0;
    for (long long value : claim.ink) {
        sum += value;
    }
    if (sum != TOTAL_INK) {
        stream.quitf(_wa, "case %d: ink total is %lld instead of %lld", caseNo, sum, TOTAL_INK);
    }

    const TestCase& tc = tests[caseNo - 1];
    for (int color = 0; color < 4; ++color) {
        if (claim.ink[color] > tc.limit[color]) {
            stream.quitf(_wa,
                         "case %d: color %d uses %lld but common printer limit is %lld",
                         caseNo,
                         color + 1,
                         claim.ink[color],
                         tc.limit[color]);
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    tests.resize(T);
    for (int tc = 0; tc < T; ++tc) {
        tests[tc].limit.fill(TOTAL_INK);
        for (int printer = 0; printer < 3; ++printer) {
            for (int color = 0; color < 4; ++color) {
                long long value = inf.readLong();
                tests[tc].limit[color] = min(tests[tc].limit[color], value);
            }
        }
    }

    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        Claim jury = readClaim(ans, caseNo);
        Claim participant = readClaim(ouf, caseNo);

        if (jury.impossible) {
            if (participant.impossible) {
                continue;
            }
            quitf(_fail, "case %d: participant provided a valid color while jury says IMPOSSIBLE", caseNo);
        }

        if (participant.impossible) {
            quitf(_wa, "case %d: participant says IMPOSSIBLE but jury provides a valid color", caseNo);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "%d case(s) accepted", T);
}
