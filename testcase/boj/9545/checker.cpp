#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct TestCase {
    bool explosive[26][26]{};
};

struct Claim {
    vector<int> side;
};

vector<TestCase> cases;

void validateGrid(InStream& stream, const TestCase& tc, int caseIndex, int side,
                  const vector<string>& grid) {
    for (int r = 0; r < side; ++r) {
        if ((int)grid[r].size() != side) {
            stream.quitf(_wa,
                         "case %d row %d has length %d instead of %d",
                         caseIndex, r + 1, (int)grid[r].size(), side);
        }
        for (int c = 0; c < side; ++c) {
            if (grid[r][c] < 'a' || grid[r][c] > 'z') {
                stream.quitf(_wa,
                             "case %d cell (%d,%d) is not a lowercase letter",
                             caseIndex, r + 1, c + 1);
            }
        }
    }

    for (int r = 0; r < side; ++r) {
        for (int c = 0; c < side; ++c) {
            int here = grid[r][c] - 'a';
            if (r + 1 < side) {
                int down = grid[r + 1][c] - 'a';
                if (tc.explosive[here][down]) {
                    stream.quitf(_wa,
                                 "case %d cells (%d,%d) and (%d,%d) form explosive pair %c%c",
                                 caseIndex, r + 1, c + 1, r + 2, c + 1,
                                 grid[r][c], grid[r + 1][c]);
                }
                if (tc.explosive[down][here]) {
                    stream.quitf(_wa,
                                 "case %d cells (%d,%d) and (%d,%d) form explosive pair %c%c",
                                 caseIndex, r + 2, c + 1, r + 1, c + 1,
                                 grid[r + 1][c], grid[r][c]);
                }
            }
            if (c + 1 < side) {
                int right = grid[r][c + 1] - 'a';
                if (tc.explosive[here][right]) {
                    stream.quitf(_wa,
                                 "case %d cells (%d,%d) and (%d,%d) form explosive pair %c%c",
                                 caseIndex, r + 1, c + 1, r + 1, c + 2,
                                 grid[r][c], grid[r][c + 1]);
                }
                if (tc.explosive[right][here]) {
                    stream.quitf(_wa,
                                 "case %d cells (%d,%d) and (%d,%d) form explosive pair %c%c",
                                 caseIndex, r + 1, c + 2, r + 1, c + 1,
                                 grid[r][c + 1], grid[r][c]);
                }
            }
        }
    }
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.side.reserve(cases.size());

    for (int tcIndex = 0; tcIndex < (int)cases.size(); ++tcIndex) {
        string first = stream.readToken("[a-z]+",
                                        format("case %d row 1", tcIndex + 1).c_str());
        int side = first.size();
        if (side < 1 || side > 20) {
            stream.quitf(_wa,
                         "case %d side length must be between 1 and 20, found %d",
                         tcIndex + 1, side);
        }

        vector<string> grid(side);
        grid[0] = first;
        for (int r = 1; r < side; ++r) {
            grid[r] = stream.readToken("[a-z]+",
                                       format("case %d row %d", tcIndex + 1, r + 1).c_str());
        }

        validateGrid(stream, cases[tcIndex], tcIndex + 1, side, grid);
        claim.side.push_back(side);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d test cases", (int)cases.size());
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        for (int i = 0; i < n; ++i) {
            string pair = inf.readToken();
            cases[tc].explosive[pair[0] - 'a'][pair[1] - 'a'] = true;
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    for (int tc = 0; tc < t; ++tc) {
        if (participant.side[tc] < jury.side[tc]) {
            quitf(_wa,
                  "case %d participant side %d is smaller than jury side %d",
                  tc + 1, participant.side[tc], jury.side[tc]);
        }
        if (participant.side[tc] > jury.side[tc]) {
            quitf(_fail,
                  "case %d participant side %d is larger than jury side %d",
                  tc + 1, participant.side[tc], jury.side[tc]);
        }
    }

    quitf(_ok, "all %d grid claims match the jury baseline", t);
}
