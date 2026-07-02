#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool possible;
};

int n;
long long target;

long long scoreDifference(const vector<int>& cards) {
    int left = 0;
    int right = n - 1;
    long long alice = 0;
    long long bob = 0;

    for (int turn = 0; turn < n; ++turn) {
        int picked;
        if (cards[left] > cards[right]) {
            picked = cards[left++];
        } else {
            picked = cards[right--];
        }

        if (turn % 2 == 0) {
            alice += picked;
        } else {
            bob += picked;
        }
    }

    return alice - bob;
}

Claim readClaim(InStream& stream, int caseIndex) {
    string verdict = stream.readToken();
    if (verdict == "NO") {
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "case %d verdict is %s, expected YES or NO", caseIndex, verdict.c_str());
    }

    vector<int> cards(n);
    vector<int> used(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        cards[i] = stream.readInt(1, n, format("case %d card[%d]", caseIndex, i + 1).c_str());
        if (used[cards[i]]) {
            stream.quitf(_wa, "case %d repeats card %d", caseIndex, cards[i]);
        }
        used[cards[i]] = 1;
    }

    long long diff = scoreDifference(cards);
    if (diff != target) {
        stream.quitf(_wa,
                     "case %d has score difference %lld instead of %lld",
                     caseIndex,
                     diff,
                     target);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    for (int tc = 1; tc <= tests; ++tc) {
        n = inf.readInt();
        target = inf.readLong();

        Claim jury = readClaim(ans, tc);
        Claim participant = readClaim(ouf, tc);

        if (jury.possible && !participant.possible) {
            quitf(_wa, "case %d is possible according to jury, but participant printed NO", tc);
        }
        if (!jury.possible && participant.possible) {
            quitf(_fail, "case %d has a valid participant witness while jury printed NO", tc);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d case(s) are valid", tests);
}
