#include "testlib.h"

#include <vector>
using namespace std;

struct Interval {
    long long start;
    long long end;
};

int n;
vector<Interval> intervals;

struct Answer {
    int lions;
    int tigers;

    int value() const {
        return min(lions, tigers);
    }
};

bool overlaps(const Interval& a, const Interval& b) {
    return a.start < b.end && b.start < a.end;
}

Answer readAnswer(InStream& stream) {
    vector<int> assignment(n);
    int lions = 0;
    int tigers = 0;

    for (int i = 0; i < n; ++i) {
        assignment[i] = stream.readInt(0, 2, format("assignment[%d]", i + 1).c_str());
        if (assignment[i] == 1) {
            ++lions;
        } else if (assignment[i] == 2) {
            ++tigers;
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d assignments", n);
    }

    for (int i = 0; i < n; ++i) {
        if (assignment[i] == 0) {
            continue;
        }
        for (int j = i + 1; j < n; ++j) {
            if (assignment[j] == 0 || assignment[i] == assignment[j]) {
                continue;
            }
            if (overlaps(intervals[i], intervals[j])) {
                stream.quitf(_wa,
                             "performances %d and %d overlap but use different animals: %d and %d",
                             i + 1,
                             j + 1,
                             assignment[i],
                             assignment[j]);
            }
        }
    }

    return {lions, tigers};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 200, "n");
    intervals.resize(n);
    for (int i = 0; i < n; ++i) {
        long long s = inf.readLong(0, 1000000000LL, format("s[%d]", i + 1).c_str());
        long long t = inf.readLong(1, 1000000000LL, format("t[%d]", i + 1).c_str());
        intervals[i] = {s, s + t};
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    int juryValue = jury.value();
    int participantValue = participant.value();

    if (participantValue < juryValue) {
        quitf(_wa,
              "participant answer is worse than jury: participant=%d jury=%d",
              participantValue,
              juryValue);
    }
    if (participantValue > juryValue) {
        quitf(_fail,
              "participant answer is better than jury: participant=%d jury=%d",
              participantValue,
              juryValue);
    }

    quitf(_ok, "answer=%d", participantValue);
}
