#include "testlib.h"

#include <vector>

using namespace std;

struct Interval {
    int lo;
    int hi;
};

struct Answer {
    long long cost;
};

int n;
vector<Interval> intervals;

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0, 1000000000000000000LL, "total cost");
    stream.readEoln();

    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = stream.readInt(intervals[i].lo, intervals[i].hi,
                                   format("stress[%d]", i + 1).c_str());
        stream.readEoln();
    }
    stream.readEof();

    long long actual = 0;
    for (int i = 1; i < n; ++i) {
        actual += abs(values[i] - values[i - 1]);
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed total cost %lld does not match witness cost %lld",
                     claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    intervals.resize(n);
    for (int i = 0; i < n; ++i) {
        intervals[i].lo = inf.readInt();
        intervals[i].hi = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cost < jury.cost) {
        quitf(_fail, "participant found better answer: jury=%lld participant=%lld",
              jury.cost, participant.cost);
    }
    if (participant.cost > jury.cost) {
        quitf(_wa, "jury has better answer: jury=%lld participant=%lld",
              jury.cost, participant.cost);
    }

    quitf(_ok, "answer=%lld", participant.cost);
}
