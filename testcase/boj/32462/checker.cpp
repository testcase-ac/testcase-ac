#include "testlib.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<long long> coins;
};

vector<long long> testN;

vector<long long> greedyRepresentation(long long amount, const vector<long long>& coinsDesc) {
    vector<long long> representation(coinsDesc.size());
    for (int i = 0; i < int(coinsDesc.size()); ++i) {
        representation[i] = amount / coinsDesc[i];
        amount %= coinsDesc[i];
    }
    return representation;
}

long long coinCount(const vector<long long>& representation) {
    long long result = 0;
    for (long long value : representation) {
        result += value;
    }
    return result;
}

long long firstGreedyCounterexample(const vector<long long>& coinsAsc) {
    vector<long long> coinsDesc(coinsAsc.rbegin(), coinsAsc.rend());
    const int n = int(coinsDesc.size());
    const long long none = numeric_limits<long long>::max();
    long long best = none;

    for (int i = 1; i < n; ++i) {
        vector<long long> candidate = greedyRepresentation(coinsDesc[i - 1] - 1, coinsDesc);
        for (int j = i; j < n; ++j) {
            vector<long long> representation = candidate;
            ++representation[j];
            for (int k = j + 1; k < n; ++k) {
                representation[k] = 0;
            }

            long long amount = 0;
            for (int k = 0; k < n; ++k) {
                amount += representation[k] * coinsDesc[k];
            }

            vector<long long> greedy = greedyRepresentation(amount, coinsDesc);
            if (coinCount(representation) < coinCount(greedy)) {
                best = min(best, amount);
            }
        }
    }
    return best;
}

void validateConstructedClaim(InStream& stream, const Claim& claim, int caseIndex) {
    if (claim.impossible) {
        return;
    }
    long long firstBad = firstGreedyCounterexample(claim.coins);
    if (firstBad != testN[caseIndex]) {
        if (firstBad == numeric_limits<long long>::max()) {
            stream.quitf(_wa, "case %d: coin set is canonical, but N is %lld",
                         caseIndex + 1, testN[caseIndex]);
        }
        stream.quitf(_wa, "case %d: first greedy counterexample is %lld, expected %lld",
                     caseIndex + 1, firstBad, testN[caseIndex]);
    }
}

Claim readClaim(InStream& stream, int caseIndex) {
    int first = stream.readInt(-1, 30, format("case %d first token", caseIndex + 1).c_str());
    if (first == -1) {
        return {true, {}};
    }
    int k = first;
    if (k < 1) {
        stream.quitf(_wa, "case %d: K must be at least 1", caseIndex + 1);
    }

    vector<long long> coins(k);
    for (int i = 0; i < k; ++i) {
        coins[i] = stream.readLong(1, 1000000000LL,
                                   format("case %d coin[%d]", caseIndex + 1, i + 1).c_str());
    }

    if (coins[0] != 1) {
        stream.quitf(_wa, "case %d: first coin is %lld, expected 1", caseIndex + 1, coins[0]);
    }
    for (int i = 1; i < k; ++i) {
        if (coins[i - 1] >= coins[i]) {
            stream.quitf(_wa, "case %d: coins must be strictly increasing at positions %d and %d",
                         caseIndex + 1, i, i + 1);
        }
    }
    return {false, coins};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    testN.resize(t);
    for (int i = 0; i < t; ++i) {
        testN[i] = inf.readLong();
    }

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        Claim jury = readClaim(ans, caseIndex);
        validateConstructedClaim(ans, jury, caseIndex);

        Claim participant = readClaim(ouf, caseIndex);
        validateConstructedClaim(ouf, participant, caseIndex);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant found a valid coin set while jury reports impossible",
                  caseIndex + 1);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: jury has a valid coin set, but participant printed -1",
                  caseIndex + 1);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }
    quitf(_ok, "all %d cases are valid", t);
}
