#include "testlib.h"

#include <vector>

using namespace std;

const unsigned long long THRESHOLD = 0x0123456789ABCDEFULL;
const long long MAX_X = 1000000000000000000LL;

int n;
vector<unsigned long long> lowerBound;
vector<unsigned long long> upperBound;

struct Answer {
    bool impossible;
    unsigned long long x;
};

bool evaluate(unsigned long long x) {
    unsigned long long value = x;
    for (int i = 0; i < n; ++i) {
        unsigned long long l = lowerBound[i];
        unsigned long long r = upperBound[i];
        if (l <= x && x <= r) {
            unsigned long long update = (x | l) + (x & r) * (l ^ r);
            value ^= update;
        }
    }
    return value >= THRESHOLD;
}

Answer readAnswer(InStream& stream) {
    long long value = stream.readLong(-1, MAX_X, "answer");
    stream.readEoln();
    stream.readEof();

    if (value == -1) {
        return {true, 0};
    }

    unsigned long long x = static_cast<unsigned long long>(value);
    if (evaluate(x)) {
        stream.quitf(_wa, "f(x) must be false for x=%lld", value);
    }
    if (!evaluate(x + 1)) {
        stream.quitf(_wa, "f(x+1) must be true for x=%lld", value);
    }
    return {false, x};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    lowerBound.resize(n);
    upperBound.resize(n);
    for (int i = 0; i < n; ++i) {
        lowerBound[i] = static_cast<unsigned long long>(inf.readLong());
    }
    for (int i = 0; i < n; ++i) {
        upperBound[i] = static_cast<unsigned long long>(inf.readLong());
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid answer while jury reports impossible: %llu",
              participant.x);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid answer %llu, participant reports impossible", jury.x);
    }

    quitf(_ok, "valid answer %llu", participant.x);
}
