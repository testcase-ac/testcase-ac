#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<long long> efficiency;

struct Answer {
    int count;
    long long score;
};

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(1, n, "module count");
    stream.readEoln();

    vector<int> used(n + 1, 0);
    long long sum = 0;
    long long lowest = 0;
    long long highest = 0;

    for (int i = 0; i < count; ++i) {
        int index = stream.readInt(1, n, format("module[%d]", i + 1).c_str());
        if (used[index]) {
            stream.quitf(_wa, "module %d is selected more than once", index);
        }
        used[index] = 1;

        long long value = efficiency[index];
        sum += value;
        if (i == 0) {
            lowest = highest = value;
        } else {
            lowest = min(lowest, value);
            highest = max(highest, value);
        }
    }

    stream.readEoln();
    stream.readEof();

    return {count, sum + lowest + highest};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 200000, "N");
    efficiency.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        efficiency[i] = inf.readLong(1, 1000000000LL, format("A[%d]", i).c_str());
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.score < jury.score) {
        quitf(_wa,
              "jury has better score: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail,
              "participant found better score: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }

    quitf(_ok, "score=%lld, modules=%d", participant.score, participant.count);
}
