#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

int n, p, k, d;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    string first = stream.readToken("[A-Za-z]+|[+-]?[0-9]+", "first output token");

    if (first == "Wrong") {
        string second = stream.readToken("[A-Za-z]+", "sentinel second token");
        if (second != "information") {
            stream.quitf(_wa, "expected sentinel 'Wrong information', found 'Wrong %s'", second.c_str());
        }
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after sentinel");
        }
        return {true};
    }

    long long firstScore = stringToLongLong(stream, first);
    if (firstScore < 0 || firstScore > p) {
        stream.quitf(_wa, "score[1]=%lld is outside [0, %d]", firstScore, p);
    }

    vector<long long> scores(n);
    scores[0] = firstScore;
    long long sum = firstScore;

    for (int i = 1; i < n; ++i) {
        scores[i] = stream.readLong(0LL, (long long)p, format("score[%d]", i + 1).c_str());
        if (scores[i - 1] < scores[i]) {
            stream.quitf(_wa,
                         "scores are not in descending order at positions %d and %d: %lld < %lld",
                         i,
                         i + 1,
                         scores[i - 1],
                         scores[i]);
        }
        sum += scores[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after standings");
    }

    if (sum != p) {
        stream.quitf(_wa, "score sum is %lld instead of %d", sum, p);
    }

    set<long long> topScores;
    for (int i = 0; i < k; ++i) {
        topScores.insert(scores[i]);
    }
    if ((int)topScores.size() != d) {
        stream.quitf(_wa,
                     "top %d scores have %d distinct values instead of %d",
                     k,
                     (int)topScores.size(),
                     d);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    p = inf.readInt();
    k = inf.readInt();
    d = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid standing while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid standing");
    }

    quitf(_ok, "valid standing");
}
