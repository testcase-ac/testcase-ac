#include "testlib.h"

#include <array>
#include <string>

using namespace std;

struct TestCase {
    long long mx;
    long long my;
    string moves;
};

struct Claim {
    bool impossible;
};

int moveIndex(char c) {
    if (c == 'U') return 0;
    if (c == 'D') return 1;
    if (c == 'L') return 2;
    if (c == 'R') return 3;
    return -1;
}

Claim readClaim(InStream& stream, const TestCase& tc, int caseNo) {
    string token = stream.readToken();
    if (token == "Impossible") {
        return {true};
    }

    if (token.size() != tc.moves.size()) {
        stream.quitf(_wa,
                     "case %d: output length is %d, expected %d",
                     caseNo,
                     (int)token.size(),
                     (int)tc.moves.size());
    }

    array<int, 4> expected{};
    array<int, 4> actual{};
    for (char c : tc.moves) {
        expected[moveIndex(c)]++;
    }

    long long x = 0;
    long long y = 0;
    if (x == tc.mx && y == tc.my) {
        stream.quitf(_wa, "case %d: robot starts on the mine", caseNo);
    }

    for (int i = 0; i < (int)token.size(); ++i) {
        int id = moveIndex(token[i]);
        if (id == -1) {
            stream.quitf(_wa, "case %d: invalid move '%c' at position %d", caseNo, token[i], i + 1);
        }
        actual[id]++;

        if (token[i] == 'U') y++;
        if (token[i] == 'D') y--;
        if (token[i] == 'L') x--;
        if (token[i] == 'R') x++;

        if (x == tc.mx && y == tc.my) {
            stream.quitf(_wa,
                         "case %d: robot reaches the mine after %d moves",
                         caseNo,
                         i + 1);
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (actual[i] != expected[i]) {
            stream.quitf(_wa,
                         "case %d: output is not a rearrangement of the input string",
                         caseNo);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        TestCase tc;
        tc.mx = inf.readLong();
        tc.my = inf.readLong();
        tc.moves = inf.readToken();

        Claim jury = readClaim(ans, tc, caseNo);
        Claim participant = readClaim(ouf, tc, caseNo);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant found a valid answer but jury says Impossible", caseNo);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: participant says Impossible but jury has a valid answer", caseNo);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all claims are valid and consistent with jury output");
}
