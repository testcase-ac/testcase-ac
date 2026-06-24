#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Interval {
    long long start;
    long long end;
};

struct Claim {
    int size;
};

int n;
vector<Interval> intervals;

Claim readClaim(InStream& stream) {
    int size = stream.readInt(1, n, "clique size");

    vector<char> used(n + 1, 0);
    long long left = 1;
    long long right = 1000000000LL;

    for (int i = 0; i < size; ++i) {
        int vertex = stream.readInt(1, n, format("vertex[%d]", i + 1).c_str());
        if (used[vertex]) {
            stream.quitf(_wa, "vertex %d appears more than once", vertex);
        }
        used[vertex] = 1;

        const Interval& interval = intervals[vertex];
        left = max(left, interval.start);
        right = min(right, interval.end);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d vertices", size);
    }

    if (left > right) {
        stream.quitf(_wa, "selected vertices do not form a clique");
    }

    return {size};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    intervals.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        intervals[i].start = inf.readLong();
        intervals[i].end = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.size < jury.size) {
        quitf(_wa, "jury has a larger clique: jury=%d participant=%d",
              jury.size,
              participant.size);
    }
    if (participant.size > jury.size) {
        quitf(_fail, "participant found a larger clique: jury=%d participant=%d",
              jury.size,
              participant.size);
    }

    quitf(_ok, "maximum clique size %d", participant.size);
}
