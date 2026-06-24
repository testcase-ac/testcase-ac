#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

int V, P;
int64 L;
vector<int64> villages;
map<int64, int> villageCount;

struct Answer {
    int64 claimedCost;
    int64 actualCost;
    vector<int64> offices;
};

int64 circularDistance(int64 a, int64 b) {
    int64 diff = llabs(a - b);
    return min(diff, L - diff);
}

int64 computeCost(const vector<int64>& offices) {
    i128 total = 0;
    for (int64 village : villages) {
        int64 best = L;
        for (int64 office : offices) {
            best = min(best, circularDistance(village, office));
        }
        total += best;
    }
    if (total > numeric_limits<int64>::max()) {
        quitf(_fail, "computed distance sum overflows int64");
    }
    return (int64)total;
}

Answer readAnswer(InStream& stream) {
    int64 claimedCost = stream.readLong(0LL, numeric_limits<int64>::max(), "S");
    stream.readEoln();

    vector<int64> offices(P);
    map<int64, int> used;
    for (int i = 0; i < P; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        offices[i] = stream.readLong(0LL, L - 1, format("office[%d]", i + 1).c_str());
        if (i > 0 && offices[i - 1] > offices[i]) {
            stream.quitf(_wa,
                         "office positions must be nondecreasing: office[%d]=%lld, office[%d]=%lld",
                         i, offices[i - 1], i + 1, offices[i]);
        }
        if (!villageCount.count(offices[i])) {
            stream.quitf(_wa, "office[%d]=%lld is not a village position", i + 1, offices[i]);
        }
        ++used[offices[i]];
        if (used[offices[i]] > villageCount[offices[i]]) {
            stream.quitf(_wa,
                         "office position %lld is used %d times, but only %d village(s) have that position",
                         offices[i], used[offices[i]], villageCount[offices[i]]);
        }
    }
    stream.readEoln();
    stream.readEof();

    int64 actualCost = computeCost(offices);
    if (claimedCost != actualCost) {
        stream.quitf(_wa,
                     "claimed cost %lld does not match actual cost %lld for supplied offices",
                     claimedCost, actualCost);
    }
    return {claimedCost, actualCost, offices};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    V = inf.readInt();
    P = inf.readInt();
    L = inf.readLong();
    villages = inf.readLongs(V);
    for (int64 village : villages) {
        ++villageCount[village];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actualCost > jury.actualCost) {
        quitf(_wa,
              "participant answer is worse than jury answer: participant=%lld jury=%lld",
              participant.actualCost, jury.actualCost);
    }
    if (participant.actualCost < jury.actualCost) {
        quitf(_fail,
              "participant found a better answer than jury: participant=%lld jury=%lld",
              participant.actualCost, jury.actualCost);
    }
    quitf(_ok, "answer=%lld", participant.actualCost);
}
