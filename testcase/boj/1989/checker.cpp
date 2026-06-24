#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_SCORE = 100000000000000000LL;

int n;
vector<long long> a;
vector<long long> prefixSum;

struct Answer {
    long long claimedScore;
    int left;
    int right;
    long long intervalScore;
};

Answer readAnswer(InStream& stream) {
    long long claimedScore = stream.readLong(0, MAX_SCORE, "maximum score");
    stream.readEoln();

    int left = stream.readInt(1, n, "left endpoint");
    stream.readSpace();
    int right = stream.readInt(1, n, "right endpoint");
    stream.readEoln();
    stream.readEof();

    if (left > right) {
        stream.quitf(_wa, "left endpoint %d is greater than right endpoint %d", left, right);
    }

    long long minimum = a[left];
    for (int i = left + 1; i <= right; ++i) {
        minimum = min(minimum, a[i]);
    }

    long long sum = prefixSum[right] - prefixSum[left - 1];
    long long intervalScore = sum * minimum;
    if (claimedScore != intervalScore) {
        stream.quitf(_wa,
                     "claimed score %lld does not match interval [%d, %d] score %lld",
                     claimedScore,
                     left,
                     right,
                     intervalScore);
    }

    return {claimedScore, left, right, intervalScore};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.assign(n + 1, 0);
    prefixSum.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        a[i] = inf.readLong();
        prefixSum[i] = prefixSum[i - 1] + a[i];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.intervalScore < jury.intervalScore) {
        quitf(_wa,
              "jury has better score: jury=%lld participant=%lld",
              jury.intervalScore,
              participant.intervalScore);
    }
    if (participant.intervalScore > jury.intervalScore) {
        quitf(_fail,
              "participant found a better score: jury=%lld participant=%lld",
              jury.intervalScore,
              participant.intervalScore);
    }

    quitf(_ok, "score=%lld interval=[%d, %d]", participant.intervalScore, participant.left, participant.right);
}
