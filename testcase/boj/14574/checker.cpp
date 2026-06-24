#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

struct Claim {
    long long score;
};

int n;
vector<long long> skillValue;
vector<long long> popularity;

long long matchScore(int a, int b) {
    return (popularity[a] + popularity[b]) / llabs(skillValue[a] - skillValue[b]);
}

Claim readClaim(InStream& stream) {
    long long claimed = stream.readLong(0LL, 9000000000000000000LL, "claimed total score");
    stream.readEoln();

    vector<int> alive(n + 1, 1);
    long long actual = 0;

    for (int i = 1; i <= n - 1; ++i) {
        int loser = stream.readInt(1, n, format("loser[%d]", i).c_str());
        stream.readSpace();
        int winner = stream.readInt(1, n, format("winner[%d]", i).c_str());
        stream.readEoln();

        if (loser == winner) {
            stream.quitf(_wa, "match %d uses the same chef %d twice", i, loser);
        }
        if (!alive[loser]) {
            stream.quitf(_wa, "match %d loser %d has already gone to heaven", i, loser);
        }
        if (!alive[winner]) {
            stream.quitf(_wa, "match %d winner %d has already gone to heaven", i, winner);
        }

        actual += matchScore(loser, winner);
        alive[winner] = 0;
    }

    stream.readEof();

    if (claimed != actual) {
        stream.quitf(_wa, "claimed total score %lld does not match schedule score %lld", claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    skillValue.assign(n + 1, 0);
    popularity.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        skillValue[i] = inf.readLong();
        popularity[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.score < jury.score) {
        quitf(_wa, "jury has better score: jury=%lld participant=%lld", jury.score, participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant found better score: jury=%lld participant=%lld", jury.score, participant.score);
    }

    quitf(_ok, "score=%lld", participant.score);
}
