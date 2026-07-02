#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> cards;
};

struct Claim {
    bool possible;
};

int parseRankToken(const string& token, InStream& stream, int testIndex, int position) {
    if (token.empty()) {
        stream.quitf(_wa, "empty token at case %d position %d", testIndex, position);
    }
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            stream.quitf(_wa,
                         "case %d position %d: expected rank, found '%s'",
                         testIndex,
                         position,
                         token.c_str());
        }
    }

    long value = strtol(token.c_str(), nullptr, 10);
    if (value < 1 || value > 13) {
        stream.quitf(_wa,
                     "case %d position %d: rank %ld is outside [1, 13]",
                     testIndex,
                     position,
                     value);
    }
    return static_cast<int>(value);
}

Claim readClaim(InStream& stream, const TestCase& tc, int testIndex) {
    string first = stream.readToken();
    if (first == "No") {
        return {false};
    }

    vector<int> remaining(14, 0);
    for (int card : tc.cards) {
        ++remaining[card];
    }

    long long playedSum = 0;
    for (int i = 0; i < tc.n; ++i) {
        string token = (i == 0)
                           ? first
                           : stream.readToken();
        int rank = parseRankToken(token, stream, testIndex, i + 1);

        if (remaining[rank] == 0) {
            stream.quitf(_wa,
                         "case %d position %d: rank %d is not available in the input multiset",
                         testIndex,
                         i + 1,
                         rank);
        }
        if (i > 0 && playedSum % rank != 0) {
            stream.quitf(_wa,
                         "case %d position %d: rank %d does not divide previously played sum %lld",
                         testIndex,
                         i + 1,
                         rank,
                         playedSum);
        }

        --remaining[rank];
        playedSum += rank;
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<TestCase> tests;
    while (true) {
        int n = inf.readInt();
        if (n == 0) {
            break;
        }

        TestCase tc;
        tc.n = n;
        tc.cards.resize(n);
        for (int i = 0; i < n; ++i) {
            tc.cards[i] = inf.readInt();
        }
        tests.push_back(tc);
    }

    for (int i = 0; i < static_cast<int>(tests.size()); ++i) {
        Claim jury = readClaim(ans, tests[i], i + 1);
        Claim participant = readClaim(ouf, tests[i], i + 1);

        if (jury.possible && !participant.possible) {
            quitf(_wa, "case %d: jury has a winning strategy but participant printed No", i + 1);
        }
        if (!jury.possible && participant.possible) {
            quitf(_fail, "case %d: participant found a valid winning strategy but jury printed No", i + 1);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "%d case(s) checked", static_cast<int>(tests.size()));
}
