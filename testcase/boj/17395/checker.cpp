#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long x0;
int n;

struct Answer {
    bool impossible;
    long long objective;
};

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1, x0, "x[1] or -1");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }

    vector<long long> sequence(n);
    sequence[0] = first;
    for (int i = 1; i < n; ++i) {
        sequence[i] = stream.readLong(0, x0, format("x[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    long long previous = x0;
    long long minDiff = x0;
    long long maxDiff = 0;
    for (int i = 0; i < n; ++i) {
        long long current = sequence[i];
        if ((current & ~previous) != 0) {
            stream.quitf(_wa,
                         "x[%d]=%lld is not obtainable from previous value %lld by clearing bits",
                         i + 1,
                         current,
                         previous);
        }
        if (current >= previous) {
            stream.quitf(_wa,
                         "x[%d]=%lld does not decrease from previous value %lld",
                         i + 1,
                         current,
                         previous);
        }

        long long diff = previous - current;
        minDiff = min(minDiff, diff);
        maxDiff = max(maxDiff, diff);
        previous = current;
    }

    if (sequence.back() != 0) {
        stream.quitf(_wa, "x[%d]=%lld is not 0", n, sequence.back());
    }

    return {false, maxDiff - minDiff};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    x0 = inf.readLong();
    n = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail,
              "participant provided a valid sequence while jury claims impossible, participant objective=%lld",
              participant.objective);
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury has objective %lld", jury.objective);
    }

    if (participant.objective > jury.objective) {
        quitf(_wa,
              "participant objective %lld is worse than jury objective %lld",
              participant.objective,
              jury.objective);
    }
    if (participant.objective < jury.objective) {
        quitf(_fail,
              "participant objective %lld is better than jury objective %lld",
              participant.objective,
              jury.objective);
    }

    quitf(_ok, "objective=%lld", participant.objective);
}
